#pragma once

#include "constants.h"

typedef enum {
	ITEM_UNKNOWN = 0,
	ITEM_LOW_HEAL_POTION = 1,
	ITEM_HEAL_POTION = 2,
	ITEM_HIGH_HEAL_POTION = 3
} ItemType;

typedef enum {
	WEAPON_UNKNOWN = 0,
	WEAPON_COOPER_SWORD = 1,
	WEAPON_IRON_SWORD = 2
} WeaponType;

typedef enum {
	ARMOR_UNKNOWN = 0,
	ARMOR_WOOD_CHESTPLATE = 1,
} ArmorType;

typedef enum {
	ITEMTAG_UNKNOWN = 0,
	ITEMTAG_ITEM = 1,
	ITEMTAG_WEAPON = 2,
	ITEMTAG_ARMOR = 3
} ItemTag;

typedef union {
	ItemType itemType;
	WeaponType weaponType;
	ArmorType armorType;
} InventoryItemUnion;

typedef struct {
	ItemTag tag;
	InventoryItemUnion data;
} InventoryItem;


typedef struct {
	// Currencies (integer)
	int gold;
	// Items (integer)
	int items[MAX_ITEM_TYPES];
	// Weapons (boolean)
	int weapons[MAX_WEAPON_TYPES];
	// Armors (boolean)
	int armors[MAX_ARMOR_TYPES];
} Inventory;

void showInventory(const Inventory* inventory);

int getGold(const Inventory* inventory);
int addGold(Inventory* inventory, const int amount);
int removeGold(Inventory* inventory, const int amount);

int hasItem(const Inventory *inventory, const ItemType itemType);
int getItem(const Inventory* inventory, const ItemType itemType);
int addItem(Inventory* inventory, const ItemType itemType, const int cnt);
int removeItem(Inventory* inventory, const ItemType itemType, const int cnt);

int hasWeapon(const Inventory *inventory, const WeaponType weaponType);
int addWeapon(Inventory *inventory, const WeaponType weaponType);
int removeWeapon(Inventory *inventory, const WeaponType weaponType);

int hasArmor(const Inventory *inventory, const ArmorType armorType);
int addArmor(Inventory *inventory, const ArmorType armorType);
int removeArmor(Inventory *inventory, const ArmorType armorType);
