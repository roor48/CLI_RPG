#pragma once

struct Enemy;  // 전방 선언

typedef struct Player {
	int health;
	int level;
} Player;

/**
 * @brief 대미지 받음
 *
 * @param *player 대미지를 받을 Player의 포인터
 * @param dmg 받을 대미지 값
 *
 * @return Player의 남은 체력 (0 이상)
 */
int onHitPlayer(Player* player, const int dmg);

/**
 * @brief 적을 공격함
 *
 * @param *player 공격하는 Player의 포인터
 * @param *skill 사용할 스킬 이름
 * @param *enemy 공격할 적 이름
 *
 * @return 적의 남은 체력 (0 이상)
 */
int attackEnemy(Player* player, const char* skill, const struct Enemy* enemy);
