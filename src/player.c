#include "../include/player.h"

#include "../include/enemy.h"
#include "../include/command.h"
#include "../include/item_stats.h"
#include "../include/inventory.h"
#include "../include/string_utils.h"

#include <stdio.h>

int healPlayer(Player* player, const int healAmount);
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

	printf("You got attacked by %s with %s dmg. Your health: %s/%s\n",
		enemy->name,
		formatNum(calculatedDmg),
		formatNum(player->health),
		formatNum(player->maxHealth));

	return player->health;
}

int attackEnemy(const Player* player, const Skill skill, struct Enemy* enemy) {
	return onHitEnemy(enemy, calculateDamage(player, skill));
}

int healPlayer(Player* player, const int healAmount) {
	player->health += healAmount;
	if (player->health > player->maxHealth) {
		player->health = player->maxHealth;
	}
	printf("You got healed. %s/%s (+%s)\n",
		formatNum(player->health),
		formatNum(player->maxHealth),
		formatNum(healAmount));
	return player->health;
}

int getSkill(Player* player, Skill skill) {
	if (skill == SKILL_UNKNOWN) {
		return -1;
	}

	printf("Unlocked skill: %s\n", SkillNameArray[skill]);
	return player->unlockedSkills[skill] = 1;
}

void givePlayerExp(Player* player, const int exp) {
	player->experience += exp;

	if (player->experience < player->maxExperience) {
		return;
	}
	printf("You got %s experience points. (%s/%s)\n",
		formatNum(exp),
		formatNum(player->experience),
		formatNum(player->maxExperience));

	int beforeLevel = player->level;
	player->level += player->experience / player->maxExperience;
	player->experience = player->experience % player->maxExperience;
	// 최대 경험치 양 로직은 추후에 추가
	// 임시로 player->level * 10으로 설정
	player->maxExperience = player->level * 10;
	
	printf("Level up! New level: %s -> %s\n", formatNum(beforeLevel), formatNum(player->level));
}

void printPlayerStatus(const Player* player) {
	printf("Printing player status...\n");
	
	printf("Health: %s/%s\n", formatNum(player->health), formatNum(player->maxHealth));
	printf("Defence: %s\n", formatNum(calculateDefence(player)));
	printf("Level: %s\n", formatNum(player->level));
	printf("Experience: %s/%s\n", formatNum(player->experience), formatNum(player->maxExperience));

	printf("Weapon: %s\n", weaponNameArray[player->currentWeapon]);
	printf("Armor: %s\n", armorNameArray[player->currentArmor]);
}

void printPlayerSkills(const Player* player) {
	printf("Unlocked skills:\n");
	for (int i = 0; i < MAX_SKILL_TYPES; i++) {
		if (player->unlockedSkills[i]) {
			printf(" - %s\n", SkillNameArray[i]);
		}
	}
}

int equipItem(Player* player, const Inventory *inventory, const Command* cmd) {
	InventoryItem inventoryItem = { 0 };

	getItemTypeFromName(cmd->arg1, &inventoryItem);
	if (inventoryItem.tag == ITEMTAG_UNKNOWN) {
		printf("Unknown item name: %s\n", cmd->arg1);
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
			dmg = (int)(dmg * 1.25);
			break;

		case SKILL_SLASH:
			dmg = (int)(dmg * 1.5);
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

int useConsumable(Player* player, Inventory* inventory, const struct Command* cmd) {
	InventoryItem inventoryItem = { 0 };

	getItemTypeFromName(cmd->arg1, &inventoryItem);
	if (inventoryItem.tag == ITEMTAG_UNKNOWN) {
		printf("Unknown item name: %s\n", cmd->arg1);
		return 0;
	}
	if (inventoryItem.tag != ITEMTAG_CONSUMABLE) {
		printf("You can only use consumable items: %s\n", cmd->arg1);
		return 0;
	}

	int hasItemResult = hasItem(inventory, &inventoryItem);
	if (hasItemResult == 0) {
		printf("You don't have any %s\n", cmd->arg1);
		return 0;
	}
	if (hasItemResult == -1) {
		return 0;
	}

	switch (inventoryItem.data.consumableType) {
		case CONSUMABLE_LOW_HEAL_POTION:
				printf("Using Low Heal Potion...\n");
				healPlayer(player, 20);
				removeConsumable(inventory, CONSUMABLE_LOW_HEAL_POTION, 1);
			break;

		case CONSUMABLE_HEAL_POTION:
			printf("Using Heal Potion...\n");
			healPlayer(player, 50);
			removeConsumable(inventory, CONSUMABLE_HEAL_POTION, 1);
			break;

		case CONSUMABLE_HIGH_HEAL_POTION:
			printf("Using High Heal Potion...\n");
			healPlayer(player, 70);
			removeConsumable(inventory, CONSUMABLE_HIGH_HEAL_POTION, 1);
			break;


		case CONSUMABLE_UNKNOWN:
		default:
			printf("Unknown consumable type\n");
			return 0;
	}

	return 1;
}