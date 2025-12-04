#include "../include/player.h"

#include "../include/enemy.h"

#include <stdio.h>

int onHitPlayer(Player* player, const int dmg) {
	if (dmg < 0) {
		return player->health;
	}
	player->health -= dmg;
	if (player->health < 0) {
		player->health = 0;
	}
	return player->health;
}

int attackEnemy(const Player* player, const Skill skill, struct Enemy* enemy) {
	int dmg = -1;
	
	switch (skill)
	{
		case SKILL_SLASH:
			dmg = 10 + (player->level);
			break;
		case SKILL_PUNCH:
			dmg = 5 + (player->level * 2);
			break;

		case SKILL_UNKNOWN:
		default:
			puts("Unknown skill");
			return -1;
	}

	int enemyHealth = onHitEnemy(enemy, dmg);

	printf("Attacked %s with %d damage. Enemy health: %d/%d\n",
		enemy->name, 
		dmg, 
		enemyHealth, 
		enemy->maxHealth);

	return enemyHealth;
}

int getSkill(Player* player, Skill skill) {
	if (skill == SKILL_UNKNOWN) {
		return -1;
	}

	return player->unlockedSkills[skill] = 1;
}

void givePlayerExp(Player* player, const int exp) {
	player->experience += exp;

	if (player->experience < player->maxExperience) {
		return;
	}

	int beforeLevel = player->level;
	player->level += player->experience / player->maxExperience;
	player->experience = player->experience % player->maxExperience;
	// 최대 경험치 양 로직은 추후에 추가
	// 임시로 player->level * 10으로 설정
	player->maxExperience = player->level * 10;

	printf("Level up! New level: %d -> %d\n", beforeLevel, player->level);
}
