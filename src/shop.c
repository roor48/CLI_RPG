#include "../include/shop.h"

#include "../include/constants.h"
#include "../include/inventory.h"
#include "../include/command.h"
#include "../include/string_utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SELL_RATE 0.5

void getItemTypeFromName(const Command *cmd, InventoryItem *inventoryItem, int *amount);

int buyItem(Inventory* inventory, const ItemType itemType, const char* itemName, const int amount);
int sellItem(Inventory* inventory, const ItemType itemType, const char* itemName, const int amount);
int buyWeapon(Inventory* inventory, const WeaponType itemType, const char* itemName);
int sellWeapon(Inventory* inventory, const WeaponType itemType, const char* itemName);
int buyArmor(Inventory* inventory, const ArmorType itemType, const char* itemName);
int sellArmor(Inventory* inventory, const ArmorType itemType, const char* itemName);

const char* itemNameArray[MAX_ITEM_TYPES + 1] = {
	[ITEM_UNKNOWN] = "unknown",
	[ITEM_LOW_HEAL_POTION] = "LowHealPotion",
	[ITEM_HEAL_POTION] = "HealPotion",
	[ITEM_HIGH_HEAL_POTION] = "HighHealPotion"
};
const int itemPriceArray[MAX_ITEM_TYPES + 1] = {
	[ITEM_UNKNOWN] = 0,
	[ITEM_LOW_HEAL_POTION] = 10,
	[ITEM_HEAL_POTION] = 25,
	[ITEM_HIGH_HEAL_POTION] = 50
};

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

const char* armorNameArray[MAX_ARMOR_TYPES + 1] = {
	[ARMOR_UNKNOWN] = "unknown",
	[ARMOR_WOOD_CHESTPLATE] = "WoodChestplate"
};
const int armorPriceArray[MAX_ARMOR_TYPES + 1] = {
	[ARMOR_UNKNOWN] = 0,
	[ARMOR_WOOD_CHESTPLATE] = 150
};

void getItemTypeFromName(const Command *cmd, InventoryItem *inventoryItem, int *amount) {
	*amount = 1;  // default 1

	// char* to int
	if (cmd->arg2[0] != '\0') {
		*amount = atoi(cmd->arg2);
		if (*amount <= 0) {
			printf("Invalid amount. Please enter a positive number.\n");
			return;
		}
	}

	// arg1을 소문자로 변환
	char itemName[MAX_ARG_LENGTH + 1];
	strcpy_s(itemName, sizeof(itemName), cmd->arg1);
	itemName[MAX_ARG_LENGTH] = '\0';

	// char* 형태를 enum으로 변환
	// ITEM
	for (int i = 1; i <= MAX_ITEM_TYPES; i++) {
		if (strcmp(itemName, itemNameArray[i]) == 0) {
			inventoryItem->data.itemType = (ItemType)i;
			inventoryItem->tag = ITEMTAG_ITEM;
			return;
		}
	}
	
	// WEAPON
	for (int i = 1; i <= MAX_WEAPON_TYPES; i++) {
		if (strcmp(itemName, weaponNameArray[i]) == 0) {
			inventoryItem->data.weaponType = (WeaponType)i;
			inventoryItem->tag = ITEMTAG_WEAPON;
			return;
		}
	}

	// ARMOR
	for (int i = 1; i <= MAX_ARMOR_TYPES; i++) {
		if (strcmp(itemName, armorNameArray[i]) == 0) {
			inventoryItem->data.armorType = (ArmorType)i;
			inventoryItem->tag = ITEMTAG_ARMOR;
			return;
		}
	}

	printf("Unknown item: %s\n", cmd->arg1);
}

void showShop() {
	printf("Welcome to the shop! Here are the items available for purchase:\n");

	int cnt = 1;
	for (int i = 1; i <= MAX_ITEM_TYPES; i++) {
		printf("%d. %s - %d Gold\n", cnt++, itemNameArray[i], itemPriceArray[i]);
	}

	for (int i = 1; i <= MAX_WEAPON_TYPES; i++) {
		printf("%d. %s - %d Gold\n", cnt++, weaponNameArray[i], weaponPriceArray[i]);
	}

	for (int i = 1; i <= MAX_ARMOR_TYPES; i++) {
		printf("%d. %s - %d Gold\n", cnt++, armorNameArray[i], armorPriceArray[i]);
	}
	
	printf("Type 'buy [name] [amount]' to purchase an item.\n");
}

int buyShop(Inventory *inventory, const Command *cmd) {
	InventoryItem inventoryItem = (InventoryItem){0};
	int amount = 1;

	getItemTypeFromName(cmd, &inventoryItem, &amount);

	int currentGold = -1;

	// 아이템 구매
	switch (inventoryItem.tag) {
		case ITEMTAG_ITEM:
			currentGold = buyItem(inventory, inventoryItem.data.itemType, cmd->arg1, amount);
			break;

		case ITEMTAG_WEAPON:
			currentGold = buyWeapon(inventory, inventoryItem.data.weaponType, cmd->arg1);
			break;

		case ITEMTAG_ARMOR:
			currentGold = buyArmor(inventory, inventoryItem.data.armorType, cmd->arg1);
			break;

		default:
			printf("ERROR: Unknown item %s\n", cmd->arg1);
			break;
	}

	return currentGold;
}

int sellShop(Inventory* inventory, const Command *cmd) {
	InventoryItem inventoryItem = (InventoryItem){ 0 };
	int amount = 1;

	getItemTypeFromName(cmd, &inventoryItem, &amount);

	int currentGold = -1;

	// 아이템 판매
	switch (inventoryItem.tag) {
		case ITEMTAG_ITEM:
			currentGold = sellItem(inventory, inventoryItem.data.itemType, cmd->arg1, amount);
			break;

		case ITEMTAG_WEAPON:
			currentGold = sellWeapon(inventory, inventoryItem.data.weaponType, cmd->arg1);
			break;

		case ITEMTAG_ARMOR:
			currentGold = sellArmor(inventory, inventoryItem.data.armorType, cmd->arg1);
			break;

		default:
			printf("ERROR: Unknown item %s\n", cmd->arg1);
			break;
	}

	return currentGold;
}

// Item
int buyItem(Inventory* inventory, const ItemType itemType, const char *itemName, const int amount) {
	printf("Purchasing %d x %s\n", amount, itemName);

	int beforeGold = inventory->gold;
	int value = itemPriceArray[itemType] * amount;

	if (beforeGold < value) {
		printf("Not enough gold to purchase %d of %s\n", amount, itemName);
		return -1;
	}

	removeGold(inventory, value);
	addItem(inventory, itemType, amount);

	printf("You have purchased %d of %s.\n", amount, itemName);
	printf("%dG -> %dG (-%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}

int sellItem(Inventory* inventory, const ItemType itemType, const char *itemName, const int amount) {
	printf("Selling %d x %s\n", amount, itemName);

	int beforeGold = inventory->gold;
	int value = itemPriceArray[itemType] * amount * SELL_RATE;

	if (getItem(inventory, itemType) < amount) {
		printf("Not enough items to sell %d of %s\n", amount, itemName);
		return -1;
	}

	addGold(inventory, value);
	removeItem(inventory, itemType, amount);

	printf("You have sold %d of %s.\n", amount, itemName);
	printf("%dG -> %dG (+%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}

// Weapon
int buyWeapon(Inventory* inventory, const WeaponType weaponType, const char *itemName) {
	printf("Purchasing weapon: %s\n", itemName);

	if (hasWeapon(inventory, weaponType)) {
		printf("You already have the weapon: %s\n", itemName);
		return -1;
	}

	int beforeGold = inventory->gold;
	int value = weaponPriceArray[weaponType];

	if (beforeGold < value) {
		printf("Not enough gold to purchase %s\n", itemName);
		return -1;
	}

	removeGold(inventory, value);
	addWeapon(inventory, weaponType);
	
	printf("You have purchased the weapon: %s.\n", itemName);
	printf("%dG -> %dG (-%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}

int sellWeapon(Inventory* inventory, const WeaponType weaponType, const char *itemName) {
	printf("Selling weapon: %s\n", itemName);

	if (!hasWeapon(inventory, weaponType)) {
		printf("You have no weapon: %s to sell.\n", itemName);
		return -1;
	}

	int beforeGold = inventory->gold;
	int value = weaponPriceArray[weaponType] * SELL_RATE;

	addGold(inventory, value);
	removeWeapon(inventory, weaponType);

	printf("You have sold the weapon: %s.\n", itemName);
	printf("%dG -> %dG (+%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}

// Armor
int buyArmor(Inventory* inventory, const ArmorType armorType, const char* itemName) {
	printf("Purchasing armor: %s\n", itemName);

	if (hasArmor(inventory, armorType)) {
		printf("You already have the armor: %s\n", itemName);
		return -1;
	}

	int beforeGold = inventory->gold;
	int value = armorPriceArray[armorType];

	if (beforeGold < value) {
		printf("Not enough gold to purchase %s\n", itemName);
		return -1;
	}

	removeGold(inventory, value);
	addArmor(inventory, armorType);

	printf("You have purchased the armor: %s.\n", itemName);
	printf("%dG -> %dG (-%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}

int sellArmor(Inventory* inventory, const ArmorType armorType, const char* itemName) {
	printf("Selling armor: %s\n", itemName);

	if (!hasArmor(inventory, armorType)) {
		printf("You have no armor: %s to sell.\n", itemName);
		return -1;
	}

	int beforeGold = inventory->gold;
	int value = armorPriceArray[armorType] * SELL_RATE;

	addGold(inventory, value);
	removeArmor(inventory, armorType);

	printf("You have sold the armor: %s.\n", itemName);
	printf("%dG -> %dG (+%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}
