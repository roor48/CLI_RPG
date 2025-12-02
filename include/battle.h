#pragma once

#include "enemyManager.h"

struct Player;
struct Command;

typedef struct Battle {
	struct EnemyManager enemyManager;
} Battle;

void initBattle(Battle* battle);

void startBattle(Battle* battle);

/*
 * @brief 플레이어의 공격, 적의 공격 처리
 *
 * @param *player Player의 포인터
 * @param *battle Battle의 포인터
 * @param *cmd Command의 포인터
 *
 * @return 승리시 1 반환, 패배시 -1 반환, 진행 중일시 0 반환
 */
int attackBattle(struct Player* player, Battle* battle, const struct Command* cmd);

void printEnemy(EnemyManager* enemyManager);
