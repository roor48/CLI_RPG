#include "../include/player.h"

#include "../include/enemy.h"
#include "../include/command.h"
#include "../include/item_stats.h"
#include "../include/inventory.h"

#include <stdio.h>

int equipWeapon(Player* player, const WeaponType weaponType);
int equipArmor(Player * player, const ArmorType armorType);

const char* SkillNameArray[MAX_SKILL_TYPES] = {
	[SKILL_PUNCH] = "punch",
	[SKILL_SLASH] = "slash"
};

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

void printPlayerStatus(const Player* player) {
	printf("Printing player status...\n");
	
	printf("Health: %d/%d\n", player->health, player->maxHealth);
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
