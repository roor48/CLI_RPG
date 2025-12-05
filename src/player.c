#include "../include/player.h"

#include "../include/enemy.h"
#include "../include/command.h"
#include "../include/item_stats.h"
#include "../include/inventory.h"

#include <stdio.h>

int equipWeapon(Player* player, const WeaponType weaponType);
int equipArmor(Player * player, const ArmorType armorType);
int calculateDamage(const Player* player, const Skill skill);
int calculateDefence(const Player* player);

const char* SkillNameArray[MAX_SKILL_TYPES] = {
	[SKILL_PUNCH] = "punch",
	[SKILL_SLASH] = "slash"
};

int onHitPlayer(Player* player, const Enemy* enemy) {
	int calculatedDmg = enemy->damage - (calculateDefence(player) / 2);

	if (calculatedDmg <= 0) {
		calculatedDmg = 0;
	}

	player->health -= calculatedDmg;
	if (player->health < 0) {
		player->health = 0;
	}

	printf("You got attacked by %s with %d dmg. Your health: %d/%d\n",
		enemy->name,
		calculatedDmg,
		player->health,
		player->maxHealth);

	return player->health;
}

int attackEnemy(const Player* player, const Skill skill, struct Enemy* enemy) {
	return onHitEnemy(enemy, calculateDamage(player, skill));
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
	printf("You got %d experience points. (%d/%d)\n", exp, player->experience, player->maxExperience);

	int beforeLevel = player->level;
	player->level += player->experience / player->maxExperience;
	player->experience = player->experience % player->maxExperience;
	// 최대 경험치 양 로직은 추후에 추가
	// 임시로 player->level * 10으로 설정
	player->maxExperience = player->level * 10;
	
	printf("Level up! New level: %d -> %d\n", beforeLevel, player->level);
}

void printPlayerStatus(const Player* player) {
	printf("Printing player status...\n");
	
	printf("Health: %d/%d\n", player->health, player->maxHealth);
	printf("Defence: %d\n", calculateDefence(player));
	printf("Level: %d\n", player->level);
	printf("Experience: %d/%d\n", player->experience, player->maxExperience);

	// 임시로 번호만 출력
	printf("Weapon: %d\n", player->currentWeapon);
	printf("Armor: %d\n", player->currentArmor);
}

void printPlayerSkills(const Player* player) {
	printf("Printing player skills...\n");
	printf("Unlocked skills:\n");
	for (int i = 0; i < MAX_SKILL_TYPES; i++) {
		if (player->unlockedSkills[i]) {
			printf(" - %s\n", SkillNameArray[i]);
		}
	}
}

int equipItem(Player* player, const Inventory *inventory, const Command* cmd) {
	InventoryItem inventoryItem = { 0 };

	getItemTypeFromName(cmd, &inventoryItem);
	if (inventoryItem.tag == ITEMTAG_UNKNOWN) {
		return 0;
	}
	if (!hasItem(inventory, &inventoryItem)) {
		printf("Selected item not exists\n");
		return 0;
	}

	switch (inventoryItem.tag) {
		case ITEMTAG_WEAPON:
			return equipWeapon(player, inventoryItem.data.weaponType);

		case ITEMTAG_ARMOR:
			return equipArmor(player, inventoryItem.data.armorType);

		case ITEMTAG_CONSUMABLE:
			printf("Cannot equip consumable items\n");
			break;

		case ITEMTAG_UNKNOWN:
		default:
			printf("Unknown item type\n");
			break;
	}
	return 0;
}

int equipWeapon(Player* player, const WeaponType weaponType) {
	if (weaponType == WEAPON_UNKNOWN) {
		printf("Unknown weapon type\n");
		return 0;
	}
	player->currentWeapon = weaponType;
	return 1;
}

int equipArmor(Player* player, const ArmorType armorType) {
	if (armorType == ARMOR_UNKNOWN) {
		printf("Unknown armor type\n");
		return 0;
	}
	player->currentArmor = armorType;
	return 1;
}

// (기본 공격력) * 스킬 계수
int calculateDamage(const Player *player, const Skill skill) {
	int dmg = weaponDamageArray[player->currentWeapon] + player->level;
	switch (skill) {
		case SKILL_PUNCH:
			dmg *= 1.25;
			break;

		case SKILL_SLASH:
			dmg *= 1.5;
			break;

		case SKILL_UNKNOWN:
		default:
			return -1;
	}

	return dmg;
}

int calculateDefence(const Player* player) {
	int defence = armorDefenseArray[player->currentArmor] + player->level;
	return defence;
}

