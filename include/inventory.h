#pragma once

typedef enum {
	ITEM_LOW_HEAL_POTION,
	ITEM_HEAL_POTION,
	ITEM_HIGH_HEAL_POTION,
	ITEM_UNKNOWN
} ItemType;

typedef enum {
	WEAPON_COOPER_SWORD,
	WEAPON_IRON_SWORD,
	WEAPON_UNKNOWN
} WeaponType;

typedef enum {
	ARMOR_WOOD_CHESTPLATE,
	ARMOR_UNKNOWN
} ArmorType;

typedef struct {
	// Items (integer)
	int lowHealPotion;
	int healPotion;
	int highHealPotion;

	// Weapons (boolean)
	int cooperSword;
	int ironSword;

	// Armors (boolean)
	int woodChestplate;
} Inventory;

int hasItem(Inventory *inventory, ItemType itemType);
int addItem(Inventory* inventory, ItemType itemType, int cnt);
//int addItem(Inventory *inventory, ItemType itemType);
int removeItem(Inventory* inventory, ItemType itemType, int cnt);
//int removeItem(Inventory *inventory, ItemType itemType);

int hasWeapon(Inventory *inventory, WeaponType weaponType);
int getWeapon(Inventory *inventory, WeaponType weaponType);
int removeWeapon(Inventory *inventory, WeaponType weaponType);

int hasArmor(Inventory *inventory, ArmorType armorType);
int getArmor(Inventory *inventory, ArmorType armorType);
int removeArmor(Inventory *inventory, ArmorType armorType);
