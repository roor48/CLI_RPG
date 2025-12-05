#include "../include/item_stats.h"

#include "../include/constants.h"
#include "../include/inventory.h"
#include "../include/command.h"

#include <string.h>

// 소모템
const char* consumableNameArray[MAX_CONSUMABLE_TYPES] = {
	[CONSUMABLE_LOW_HEAL_POTION] = "LowHealPotion",
	[CONSUMABLE_HEAL_POTION] = "HealPotion",
	[CONSUMABLE_HIGH_HEAL_POTION] = "HighHealPotion"
};
const int consumablePriceArray[MAX_CONSUMABLE_TYPES] = {
	[CONSUMABLE_LOW_HEAL_POTION] = 10,
	[CONSUMABLE_HEAL_POTION] = 25,
	[CONSUMABLE_HIGH_HEAL_POTION] = 50
};

// 무기
const char* weaponNameArray[MAX_WEAPON_TYPES] = {
	[WEAPON_STICK] = "Stick",
	[WEAPON_COOPER_SWORD] = "CooperSword",
	[WEAPON_IRON_SWORD] = "IronSword"
};
const int weaponPriceArray[MAX_WEAPON_TYPES] = {
	[WEAPON_STICK] = 0,
	[WEAPON_COOPER_SWORD] = 100,
	[WEAPON_IRON_SWORD] = 200
};
const int weaponDamageArray[MAX_WEAPON_TYPES] = {
	[WEAPON_STICK] = 5,
	[WEAPON_COOPER_SWORD] = 7,
	[WEAPON_IRON_SWORD] = 9
};

// 방어구
const char* armorNameArray[MAX_ARMOR_TYPES] = {
	[ARMOR_CLOTH] = "Cloth",
	[ARMOR_WOOD_CHESTPLATE] = "WoodChestplate"
};
const int armorPriceArray[MAX_ARMOR_TYPES] = {
	[ARMOR_CLOTH] = 0,
	[ARMOR_WOOD_CHESTPLATE] = 150
};
const int armorDefenseArray[MAX_ARMOR_TYPES] = {
	[ARMOR_CLOTH] = 0,
	[ARMOR_WOOD_CHESTPLATE] = 5
};

void getItemTypeFromName(const Command* cmd, InventoryItem* inventoryItem) {
	// arg1을 소문자로 변환
	char itemName[MAX_ARG_LENGTH + 1];
	strcpy_s(itemName, sizeof(itemName), cmd->arg1);
	itemName[MAX_ARG_LENGTH] = '\0';

	// char* 형태를 enum으로 변환
	// ITEM
	for (int i = 0; i < MAX_CONSUMABLE_TYPES; i++) {
		if (strcmp(itemName, consumableNameArray[i]) == 0) {
			inventoryItem->data.consumableType = (ConsumableType)i;
			inventoryItem->tag = ITEMTAG_CONSUMABLE;
			return;
		}
	}

	// WEAPON
	for (int i = 0; i < MAX_WEAPON_TYPES; i++) {
		if (strcmp(itemName, weaponNameArray[i]) == 0) {
			inventoryItem->data.weaponType = (WeaponType)i;
			inventoryItem->tag = ITEMTAG_WEAPON;
			return;
		}
	}

	// ARMOR
	for (int i = 0; i < MAX_ARMOR_TYPES; i++) {
		if (strcmp(itemName, armorNameArray[i]) == 0) {
			inventoryItem->data.armorType = (ArmorType)i;
			inventoryItem->tag = ITEMTAG_ARMOR;
			return;
		}
	}

	inventoryItem->tag = ITEMTAG_UNKNOWN;
}
