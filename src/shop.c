#include "../include/shop.h"

#include "../include/constants.h"
#include "../include/inventory.h"
#include "../include/command.h"
#include "../include/string_utils.h"
#include "../include/item_stats.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SELL_RATE 0.5

void getItemAmount(const Command* cmd, int* amount);

int buyConsumable(Inventory* inventory, const ConsumableType consumableType, const char* consumableName, const int amount);
int sellConsumable(Inventory* inventory, const ConsumableType consumableType, const char* consumableName, const int amount);
int buyWeapon(Inventory* inventory, const WeaponType weaponType, const char* weaponName);
int sellWeapon(Inventory* inventory, const WeaponType weaponType, const char* weaponName);
int buyArmor(Inventory* inventory, const ArmorType armorType, const char* armorName);
int sellArmor(Inventory* inventory, const ArmorType armorType, const char* armorName);


void getItemAmount(const Command *cmd, int* amount) {
	*amount = 1;  // default 1

	// char* to int
	if (cmd->arg2[0] != '\0') {
		*amount = atoi(cmd->arg2);
		if (*amount <= 0) {
			printf("Invalid amount. Please enter a positive number.\n");
			return;
		}
	}
}

void showShop() {
	printf("Welcome to the shop! Here are the items available for purchase:\n");

	int cnt = 1;
	for (int i = 0; i < MAX_CONSUMABLE_TYPES; i++) {
		printf("%d. %s - %s Gold\n", cnt++, consumableNameArray[i], formatNum(consumablePriceArray[i]));
	}

	for (int i = 0; i < MAX_WEAPON_TYPES; i++) {
		printf("%d. %s - %s Gold\n", cnt++, weaponNameArray[i], formatNum(weaponPriceArray[i]));
	}

	for (int i = 0; i < MAX_ARMOR_TYPES; i++) {
		printf("%d. %s - %s Gold\n", cnt++, armorNameArray[i], formatNum(armorPriceArray[i]));
	}

	printf("Type 'buy [name] [amount]' to purchase an item.\n");
}

int buyShop(Inventory* inventory, const Command* cmd) {
	InventoryItem inventoryItem = (InventoryItem){ 0 };
	int amount = 1;

	getItemTypeFromName(cmd, &inventoryItem);
	getItemAmount(cmd, &amount);


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

		case ITEMTAG_UNKNOWN:
		default:
			printf("ERROR: Unknown item %s\n", cmd->arg1);
			break;
	}

	return currentGold;
}

int sellShop(Inventory* inventory, const Command* cmd) {
	InventoryItem inventoryItem = (InventoryItem){ 0 };
	int amount = 1;

	getItemTypeFromName(cmd, &inventoryItem);
	getItemAmount(cmd, &amount);

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

		case ITEMTAG_UNKNOWN:
		default:
			printf("ERROR: Unknown item %s\n", cmd->arg1);
			break;
	}

	return currentGold;
}

// Consumable
int buyConsumable(Inventory* inventory, const ConsumableType consumableType, const char* consumableName, const int amount) {
	printf("Purchasing %s x %s\n", formatNum(amount), consumableName);


	int beforeGold = inventory->gold;
	// **오버플로우 가능성 있음!!!**
	int value = consumablePriceArray[consumableType] * amount;

	if (inventory->gold < value) {
		printf("Not enough gold to purchase %s of %s\n", formatNum(amount), consumableName);
		return -1;
	}

	removeGold(inventory, value);
	addConsumable(inventory, consumableType, amount);

	printf("You have purchased %s of %s.\n", formatNum(amount), consumableName);
	printf("%sG -> %sG (-%s)\n", formatNum(beforeGold), formatNum(inventory->gold), formatNum(value));

	return inventory->gold;
}

int sellConsumable(Inventory* inventory, const ConsumableType consumableType, const char* consumableName, const int amount) {
	printf("Selling %s x %s\n", formatNum(amount), consumableName);

	int beforeGold = inventory->gold;
	int value = (int)(consumablePriceArray[consumableType] * amount * SELL_RATE);

	if (getConsumable(inventory, consumableType) < amount) {
		printf("Not enough consumables to sell %s of %s\n", formatNum(amount), consumableName);
		return -1;
	}

	addGold(inventory, value);
	removeConsumable(inventory, consumableType, amount);

	printf("You have sold %s of %s.\n", formatNum(amount), consumableName);
	printf("%sG -> %sG (+%s)\n", formatNum(beforeGold), formatNum(inventory->gold), formatNum(value));

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
	printf("%sG -> %sG (-%s)\n", formatNum(beforeGold), formatNum(inventory->gold), formatNum(value));

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
	printf("%sG -> %sG (+%s)\n", formatNum(beforeGold), formatNum(inventory->gold), formatNum(value));

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
	printf("%sG -> %sG (-%s)\n", formatNum(beforeGold), formatNum(inventory->gold), formatNum(value));

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
	printf("%sG -> %sG (+%s)\n", formatNum(beforeGold), formatNum(inventory->gold), formatNum(value));

	return inventory->gold;
}
