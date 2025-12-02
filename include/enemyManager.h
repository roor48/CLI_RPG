#pragma once

#include "constants.h"
#include "enemy.h"

struct Player;

typedef struct EnemyManager {
	Enemy enemies[MAX_ENEMY_COUNT];
	int enemyCount;
	int enemyRemain;
} EnemyManager;

/*
 * @brief EnemyManager 초기화
 *
 * @param *manager EnemyManager의 포인터
 */
void initEnemyManager(EnemyManager *manager);

/*
 * @brief id로 Enemy 검색
 *
 * @param *manager EnemyManager의 포인터
 * @param id 검색할 Enemy의 id
 *
 * @return 검색된 Enemy 구조체
 */
Enemy* getEnemyById(const EnemyManager *manager, const int id);

/*
 * @brief name으로 Enemy 검색
 *
 * @param *manager EnemyManager의 포인터
 * @param name 검색할 Enemy의 이름
 *
 * @return 검색된 Enemy 구조체
 */
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

/**
 * @brief 모든 Enemy가 Player를 공격
 *
 * @param *manager EnemyManager의 포인터
 * @param *player Player의 포인터
 *
 * @return 남은 Player의 체력 (0 이상)
 */
int allEnemyAttackPlayer(EnemyManager *manager, struct Player *player);

/*
 * @brief 남은 적의 수 반환
 *
 * @param *manager EnemyManager의 포인터
 *
 * @return 남은 적의 수
 */
int remainEnemies(const EnemyManager* manager);
