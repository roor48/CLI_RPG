#pragma once

#include "constants.h"
#include "enemy.h"

typedef struct EnemyManager {
	Enemy enemies[MAX_ENEMY_COUNT];
	int enemyCount;
} EnemyManager;

void initEnemyManager(EnemyManager *manager);
Enemy* getEnemyById(const EnemyManager *manager, const int id);
Enemy* getEnemyByName(const EnemyManager *manager, const char *name);

/**
 * @brief Enemy 생성
 *
 * @param *manager EnemyManager의 포인터
 * @param *name Enemy의 이름
 * @param health Enemy의 체력
 * @param damage Enemy의 대미지
 *
 * @return 생성된 Enemy 구조체
 */
Enemy *instantiateEnemy(EnemyManager *manager, const char* name, const int health, const int damage);
