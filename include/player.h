#pragma once

#include "constants.h"

struct Enemy;
enum WeaponType;
enum ArmorType;

typedef struct Player {
	int maxHealth;							// 최대 체력
	int health;								// 체력
	int level;								// 레벨
	int unlockedSkills[MAX_SKILL_TYPES];	// 스킬 목록 (해금됐으면 1, 아니면 0)

	enum WeaponType currentWeapon;			// 사용 중인 무기
	enum ArmorType currentArmor;			// 사용 중인 방어구
} Player;

typedef enum Skill {
	SKILL_UNKNOWN = 0,
	SKILL_PUNCH = 1,
	SKILL_SLASH = 2
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

/*
 * @brief 플레이어의 스킬 해금
 * 
 * @param *player Player의 포인터
 * @param skill 해금할 스킬
 * 
 * @return 성공 시 1 반환, 오류 시 -1 반환
 */
int getSkill(Player *player, Skill skill);
