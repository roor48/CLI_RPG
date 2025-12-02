#pragma once

struct Enemy;

typedef struct Player {
	int health;
	int level;
} Player;

typedef enum Skill {
	SKILL_UNKNOWN = 0,
	SKILL_SLASH = 1,
	SKILL_PUNCH = 2
} Skill;

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
 * @return 오류 시 -1 반환
 */
int attackEnemy(const Player* player, const Skill skill, struct Enemy* enemy);
