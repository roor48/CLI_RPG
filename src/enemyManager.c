#include "../include/enemyManager.h"

#include "../include/constants.h"
#include "../include/player.h"
#include "../include/enemy.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ENEMY_HP_OFFSET 0.10
#define ENEMY_DMG_OFFSET 0.05

/**
 * @brief 새로운 Enemy id 생성
 * 
 * @param *manager EnemyManager의 포인터
 * 
 * @return 새로운 Enemy id
 */
int getEnemyId(EnemyManager* manager);

/**
 * @brief Enemy 생성
 * 
 * Enemy 생성 후 enemies[MAX_ENEMY_COUNT]에 넣음
 * 
 * @param *manager EnemyManager의 포인터
 * @param *name Enemy의 이름
 * @param health Enemy의 체력
 * @param damage Enemy의 대미지
 *
 * @return 생성된 Enemy 구조체
 */
Enemy* instantiateEnemy(EnemyManager* manager, EnemyType enemyType);

const char* enemyNameArray[MAX_ENEMY_TYPES] = {
	[ENEMY_ZOMBIE] = "Zombie",
	[ENEMY_SKELETON] = "Skeleton",
	[ENEMY_SLIME] = "Slime"
};
const int enemyHpArray[MAX_ENEMY_TYPES] = {
	[ENEMY_ZOMBIE] = 30,
	[ENEMY_SKELETON] = 20,
	[ENEMY_SLIME] = 40
};
const int enemyDmgArray[MAX_ENEMY_TYPES] = {
	[ENEMY_ZOMBIE] = 5,
	[ENEMY_SKELETON] = 7,
	[ENEMY_SLIME] = 2
};

void initEnemyManager(EnemyManager* manager) {
	manager->enemyRemain = 0;
	manager->enemyIdCounter = 0;
}

void spawnEnemy(EnemyManager* manager) {
	int enemyCnt = (rand() % 3) + 1; // 1..=3
	for (;enemyCnt--;) {
		EnemyType enemyType = (EnemyType)(rand() % MAX_ENEMY_TYPES); // 0..MAX_ENEMY_TYPES

		Enemy* enemy = instantiateEnemy(manager, enemyType);
		if (enemy == NULL) {
			printf("Error: Unknown enemy type: %d\n", enemyType);
			continue;
		}
	}
}

int getEnemyId(EnemyManager* manager) {
	return manager->enemyIdCounter++; // 처음에 0 반환 후 +1
}

Enemy* instantiateEnemy(EnemyManager *manager, EnemyType enemyType) {
	if (enemyType == ENEMY_UNKNOWN) {
		return NULL;
	}
	if (manager->enemyRemain >= MAX_ENEMY_SPAWN) {
		return NULL;
	}

	int newId = getEnemyId(manager);

	manager->enemies[newId].id = newId;

	strcpy_s(manager->enemies[newId].name, sizeof(char) * (MAX_ARG_LENGTH + 1), enemyNameArray[enemyType]);
	manager->enemies[newId].name[MAX_ARG_LENGTH] = '\0';

	// HP: 기본값의 ±10% 변동 (0.9 ~ 1.1 배율)
	double hpMultiplier = 1.0 + (((double)rand() / RAND_MAX) * (2 * ENEMY_HP_OFFSET) - ENEMY_HP_OFFSET);
	int hp = (int)(enemyHpArray[enemyType] * hpMultiplier);
	manager->enemies[newId].maxHealth = manager->enemies[newId].health = hp;

	// DMG: 기본값의 ±5% 변동 (0.95 ~ 1.05 배율)
	double dmgMultiplier = 1.0 + (((double)rand() / RAND_MAX) * (2 * ENEMY_DMG_OFFSET) - ENEMY_DMG_OFFSET);
	int dmg = (int)(enemyDmgArray[enemyType] * dmgMultiplier);
	manager->enemies[newId].damage = dmg;

	manager->enemyRemain++;
	return &manager->enemies[newId];
}

Enemy* getEnemyById(const EnemyManager *manager, const int id) {
	if (id < 0 || id >= manager->enemyIdCounter) {
		return NULL;
	}

	Enemy* enemy = &manager->enemies[id];
	if (enemy->health > 0) {
		return enemy;
	}

	return NULL;
}

Enemy* getEnemyByName(const EnemyManager *manager, const char *name) {
	for (int i = 0; i < manager->enemyIdCounter; i++) {
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

	for (int i = 0; i < manager->enemyIdCounter; i++) {
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