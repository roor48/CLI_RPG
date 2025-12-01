#pragma once

#include "constants.h"

struct Player;

typedef struct Enemy {
	int id;
	char name[MAX_ARG_LENGTH];
	int maxHealth;
	int health;
	int damage;
} Enemy;

/**
 * @brief 적에게 대미지를 줌
 * 
 * @param *enemy 대미지를 줄 enemy의 포인터
 * @param dmg 적에게 줄 대미지 값
 * 
 * @return 적의 남은 체력 (0 이상)
 */
int onHitEnemy(Enemy *enemy, const int dmg);

/**
 * @brief Enemy가 Player를 공격
 *
 * @param *enemy Enemy의 포인터
 * @param *player Player의 포인터
 * 
 * @return Player의 남은 체력 (0 이상)
 */
int attackPlayer(const Enemy *enemy, struct Player *player);
