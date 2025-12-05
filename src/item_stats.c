#include "../include/item_stats.h"

#include "../include/constants.h"
#include "../include/inventory.h"

// 家葛袍
const char* consumableNameArray[MAX_CONSUMABLE_TYPES + 1] = {
	[CONSUMABLE_UNKNOWN] = "unknown",
	[CONSUMABLE_LOW_HEAL_POTION] = "LowHealPotion",
	[CONSUMABLE_HEAL_POTION] = "HealPotion",
	[CONSUMABLE_HIGH_HEAL_POTION] = "HighHealPotion"
};
const int consumablePriceArray[MAX_CONSUMABLE_TYPES + 1] = {
	[CONSUMABLE_UNKNOWN] = 0,
	[CONSUMABLE_LOW_HEAL_POTION] = 10,
	[CONSUMABLE_HEAL_POTION] = 25,
	[CONSUMABLE_HIGH_HEAL_POTION] = 50
};

// 公扁
const char* weaponNameArray[MAX_WEAPON_TYPES + 1] = {
	[WEAPON_UNKNOWN] = "unknown",
	[WEAPON_COOPER_SWORD] = "CooperSword",
	[WEAPON_IRON_SWORD] = "IronSword"
};
const int weaponPriceArray[MAX_WEAPON_TYPES + 1] = {
	[WEAPON_UNKNOWN] = 0,
	[WEAPON_COOPER_SWORD] = 100,
	[WEAPON_IRON_SWORD] = 200
};
const int weaponDamageArray[MAX_WEAPON_TYPES + 1] = {
	[WEAPON_UNKNOWN] = 5,
	[WEAPON_COOPER_SWORD] = 7,
	[WEAPON_IRON_SWORD] = 9
};

// 规绢备
const char* armorNameArray[MAX_ARMOR_TYPES + 1] = {
	[ARMOR_UNKNOWN] = "unknown",
	[ARMOR_WOOD_CHESTPLATE] = "WoodChestplate"
};
const int armorPriceArray[MAX_ARMOR_TYPES + 1] = {
	[ARMOR_UNKNOWN] = 0,
	[ARMOR_WOOD_CHESTPLATE] = 150
};
const int armorDefenseArray[MAX_ARMOR_TYPES + 1] = {
	[ARMOR_UNKNOWN] = 0,
	[ARMOR_WOOD_CHESTPLATE] = 5
};
