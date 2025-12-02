#include "../include/enemyManager.h"

#include "../include/constants.h"
#include "../include/player.h"
#include "../include/enemy.h"

#include <string.h>

void initEnemyManager(EnemyManager* manager) {
	manager->enemyCount = 0;
	manager->enemyRemain = 0;
}

int getEnemyId(EnemyManager* manager) {
	manager->enemyRemain++;
	return manager->enemyCount++;
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
	if (id < 0 || id >= manager->enemyCount) {
		return NULL;
	}

	Enemy* enemy = &manager->enemies[id];
	if (enemy->health > 0) {
		return enemy;
	}

	return NULL;
}

Enemy* getEnemyByName(const EnemyManager *manager, const char *name) {
	for (int i = 0; i < manager->enemyCount; i++) {
		if (strcmp(manager->enemies[i].name, name) == 0) {
			Enemy *enemy = &manager->enemies[i];

			if (enemy->health > 0) {
				return enemy;
			}
		}
	}

	return NULL;
}

int allEnemyAttackPlayer(EnemyManager* manager, Player* player) {
	int playerHealth = player->health;

	for (int i = 0; i < manager->enemyCount; i++) {
		if (manager->enemies[i].health > 0) {
			playerHealth = attackPlayer(&manager->enemies[i], player);

			if (playerHealth <= 0) {
				return 0;
			}
		}
	}

	return playerHealth;
}

int remainEnemies(const EnemyManager* manager) {
	return manager->enemyRemain;
}