#include "../include/enemyManager.h"

#include "../include/constants.h"
#include "../include/enemy.h"

#include <string.h>

int getEnemyId(EnemyManager* manager);


void initEnemyManager(EnemyManager* manager) {
	manager->enemyCount = 0;
}

int getEnemyId(EnemyManager* manager) {
	return (manager->enemyCount)++;
}

Enemy* instantiateEnemy(EnemyManager *manager, const char* name, const int health, const int damage) {
	Enemy enemy;
	enemy.id = getEnemyId(manager);

	if (name != NULL) {
		strcpy_s(enemy.name, MAX_ARG_LENGTH, name);
		enemy.name[MAX_ARG_LENGTH - 1] = '\0';
	}
	else {
		enemy.name[0] = '\0';
	}

	enemy.maxHealth = enemy.health = health;
	enemy.damage = damage;

	manager->enemies[enemy.id] = enemy;
	return &(manager->enemies[enemy.id]);
}

Enemy* getEnemyById(const EnemyManager *manager, const int id) {
	return &manager->enemies[id];
}
Enemy* getEnemyByName(const EnemyManager *manager, const char *name) {
	for (int i = 0; i < manager->enemyCount; i++) {
		if (strcmp(manager->enemies[i].name, name) == 0) {
			return &manager->enemies[i];
		}
	}

	return NULL;
}
