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

int buyConsumable(Inventory* inventory, const ConsumableType consumableType, const char* consumableName, const int amount);
int sellConsumable(Inventory* inventory, const ConsumableType consumableType, const char* consumableName, const int amount);
int buyWeapon(Inventory* inventory, const WeaponType weaponType, const char* weaponName);
int sellWeapon(Inventory* inventory, const WeaponType weaponType, const char* weaponName);
int buyArmor(Inventory* inventory, const ArmorType armorType, const char* armorName);
int sellArmor(Inventory* inventory, const ArmorType armorType, const char* armorName);

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
	for (int i = 1; i <= MAX_CONSUMABLE_TYPES; i++) {
		if (strcmp(itemName, consumableNameArray[i]) == 0) {
			inventoryItem->data.consumableType = (ConsumableType)i;
			inventoryItem->tag = ITEMTAG_CONSUMABLE;
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
	for (int i = 1; i <= MAX_CONSUMABLE_TYPES; i++) {
		printf("%d. %s - %d Gold\n", cnt++, consumableNameArray[i], consumablePriceArray[i]);
	}

	for (int i = 1; i <= MAX_WEAPON_TYPES; i++) {
		printf("%d. %s - %d Gold\n", cnt++, weaponNameArray[i], weaponPriceArray[i]);
	}

	for (int i = 1; i <= MAX_ARMOR_TYPES; i++) {
		printf("%d. %s - %d Gold\n", cnt++, armorNameArray[i], armorPriceArray[i]);
	}

	printf("Type 'buy [name] [amount]' to purchase an item.\n");
}

int buyShop(Inventory* inventory, const Command* cmd) {
	InventoryItem inventoryItem = (InventoryItem){ 0 };
	int amount = 1;

	getItemTypeFromName(cmd, &inventoryItem, &amount);

	int currentGold = -1;

	// 아이템 구매
	switch (inventoryItem.tag) {
	case ITEMTAG_CONSUMABLE:
		currentGold = buyConsumable(inventory, inventoryItem.data.consumableType, cmd->arg1, amount);
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

int sellShop(Inventory* inventory, const Command* cmd) {
	InventoryItem inventoryItem = (InventoryItem){ 0 };
	int amount = 1;

	getItemTypeFromName(cmd, &inventoryItem, &amount);

	int currentGold = -1;

	// 아이템 판매
	switch (inventoryItem.tag) {
	case ITEMTAG_CONSUMABLE:
		currentGold = sellConsumable(inventory, inventoryItem.data.consumableType, cmd->arg1, amount);
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

// Consumable
int buyConsumable(Inventory* inventory, const ConsumableType consumableType, const char* consumableName, const int amount) {
	printf("Purchasing %d x %s\n", amount, consumableName);

	int beforeGold = inventory->gold;
	int value = consumablePriceArray[consumableType] * amount;

	if (beforeGold < value) {
		printf("Not enough gold to purchase %d of %s\n", amount, consumableName);
		return -1;
	}

	removeGold(inventory, value);
	addConsumable(inventory, consumableType, amount);

	printf("You have purchased %d of %s.\n", amount, consumableName);
	printf("%dG -> %dG (-%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}

int sellConsumable(Inventory* inventory, const ConsumableType consumableType, const char* consumableName, const int amount) {
	printf("Selling %d x %s\n", amount, consumableName);

	int beforeGold = inventory->gold;
	int value = (int)(consumablePriceArray[consumableType] * amount * SELL_RATE);

	if (getConsumable(inventory, consumableType) < amount) {
		printf("Not enough consumables to sell %d of %s\n", amount, consumableName);
		return -1;
	}

	addGold(inventory, value);
	removeConsumable(inventory, consumableType, amount);

	printf("You have sold %d of %s.\n", amount, consumableName);
	printf("%dG -> %dG (+%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}

// Weapon
int buyWeapon(Inventory* inventory, const WeaponType weaponType, const char *weaponName) {
	printf("Purchasing weapon: %s\n", weaponName);

	if (hasWeapon(inventory, weaponType)) {
		printf("You already have the weapon: %s\n", weaponName);
		return -1;
	}

	int beforeGold = inventory->gold;
	int value = weaponPriceArray[weaponType];

	if (beforeGold < value) {
		printf("Not enough gold to purchase %s\n", weaponName);
		return -1;
	}

	removeGold(inventory, value);
	addWeapon(inventory, weaponType);
	
	printf("You have purchased the weapon: %s.\n", weaponName);
	printf("%dG -> %dG (-%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}

int sellWeapon(Inventory* inventory, const WeaponType weaponType, const char *weaponName) {
	printf("Selling weapon: %s\n", weaponName);

	if (!hasWeapon(inventory, weaponType)) {
		printf("You have no weapon: %s to sell.\n", weaponName);
		return -1;
	}

	int beforeGold = inventory->gold;
	int value = (int)(weaponPriceArray[weaponType] * SELL_RATE);

	addGold(inventory, value);
	removeWeapon(inventory, weaponType);

	printf("You have sold the weapon: %s.\n", weaponName);
	printf("%dG -> %dG (+%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}

// Armor
int buyArmor(Inventory* inventory, const ArmorType armorType, const char* armorName) {
	printf("Purchasing armor: %s\n", armorName);

	if (hasArmor(inventory, armorType)) {
		printf("You already have the armor: %s\n", armorName);
		return -1;
	}

	int beforeGold = inventory->gold;
	int value = armorPriceArray[armorType];

	if (beforeGold < value) {
		printf("Not enough gold to purchase %s\n", armorName);
		return -1;
	}

	removeGold(inventory, value);
	addArmor(inventory, armorType);

	printf("You have purchased the armor: %s.\n", armorName);
	printf("%dG -> %dG (-%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}

int sellArmor(Inventory* inventory, const ArmorType armorType, const char* armorName) {
	printf("Selling armor: %s\n", armorName);

	if (!hasArmor(inventory, armorType)) {
		printf("You have no armor: %s to sell.\n", armorName);
		return -1;
	}

	int beforeGold = inventory->gold;
	int value = (int)(armorPriceArray[armorType] * SELL_RATE);

	addGold(inventory, value);
	removeArmor(inventory, armorType);

	printf("You have sold the armor: %s.\n", armorName);
	printf("%dG -> %dG (+%d)\n", beforeGold, inventory->gold, value);

	return inventory->gold;
}
