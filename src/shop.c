#include "../include/shop.h"

#include "../include/constants.h"
#include "../include/inventory.h"
#include "../include/command.h"
#include "../include/string_utils.h"
#include "../include/item_stats.h"
#include "../include/player.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define SELL_RATE 0.5

/*
 * @brief amountString을 amount로 변환
 * 
 * amountString이 비어있다면 amount는 1로 설정
 */
void getItemAmount(const char* amountString, int* amount);

int buyConsumable(Inventory* inventory, const ConsumableType consumableType, const char* consumableName, const int amount);
int sellConsumable(Inventory* inventory, const ConsumableType consumableType, const char* consumableName, const int amount);
int buyWeapon(Inventory* inventory, const WeaponType weaponType, const char* weaponName);
int sellWeapon(Inventory* inventory, const struct Player* player, const WeaponType weaponType, const char* weaponName);
int buyArmor(Inventory* inventory, const ArmorType armorType, const char* armorName);
int sellArmor(Inventory* inventory, const struct Player* player, const ArmorType armorType, const char* armorName);


void getItemAmount(const char* amountString, int* amount) {
	*amount = 1;  // default 1

	// char* to int
	if (amountString[0] != '\0') {
		*amount = atoi(amountString);
		if (*amount <= 0) {
			*amount = 1;
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

	getItemTypeFromName(cmd->arg1, &inventoryItem);
	getItemAmount(cmd->arg2, &amount);


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

int sellShop(Inventory* inventory, const Player* player, const Command* cmd) {
	InventoryItem inventoryItem = (InventoryItem){ 0 };
	int amount = 1;

	getItemTypeFromName(cmd->arg1, &inventoryItem);
	getItemAmount(cmd->arg2, &amount);

	int currentGold = -1;

	// 아이템 판매
	switch (inventoryItem.tag) {
		case ITEMTAG_CONSUMABLE:
			currentGold = sellConsumable(inventory, inventoryItem.data.consumableType, cmd->arg1, amount);
			break;

		case ITEMTAG_WEAPON:
			currentGold = sellWeapon(inventory, player, inventoryItem.data.weaponType, cmd->arg1);
			break;

		case ITEMTAG_ARMOR:
			currentGold = sellArmor(inventory, player, inventoryItem.data.armorType, cmd->arg1);
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
	// 오버플로우 방지
	if (amount > (INT_MAX / consumablePriceArray[consumableType])) {
		printf("Amount is too large!\n");
		return -1;
	}

	int beforeGold = inventory->gold;
	int value = consumablePriceArray[consumableType] * amount;
	if (beforeGold < value) {
		printf("Not enough gold to purchase %s of %s\n", formatNum(amount), consumableName);
		return -1;
	}

	printf("Purchasing %s x %s\n", formatNum(amount), consumableName);

	removeGold(inventory, value);
	addConsumable(inventory, consumableType, amount);

	printf("You have purchased %s of %s.\n", formatNum(amount), consumableName);
	printf("%sG -> %sG (-%s)\n", formatNum(beforeGold), formatNum(inventory->gold), formatNum(value));

	return inventory->gold;
}

int sellConsumable(Inventory* inventory, const ConsumableType consumableType, const char* consumableName, const int amount) {
	if (getConsumable(inventory, consumableType) < amount) {
		printf("Not enough consumables to sell %s of %s\n", formatNum(amount), consumableName);
		return -1;
	}
	printf("Selling %s x %s\n", formatNum(amount), consumableName);

	int beforeGold = inventory->gold;
	int value = (int)(consumablePriceArray[consumableType] * amount * SELL_RATE);

	addGold(inventory, value);
	removeConsumable(inventory, consumableType, amount);

	printf("You have sold %s of %s.\n", formatNum(amount), consumableName);
	printf("%sG -> %sG (+%s)\n", formatNum(beforeGold), formatNum(inventory->gold), formatNum(value));

	return inventory->gold;
}

// Weapon
int buyWeapon(Inventory* inventory, const WeaponType weaponType, const char *weaponName) {
	if (hasWeapon(inventory, weaponType)) {
		printf("You already have the weapon: %s\n", weaponName);
		return -1;
	}
	printf("Purchasing weapon: %s\n", weaponName);

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

int sellWeapon(Inventory* inventory, const Player* player, const WeaponType weaponType, const char *weaponName) {
	if (!hasWeapon(inventory, weaponType)) {
		printf("You have no weapon: %s to sell.\n", weaponName);
		return -1;
	}
	if (player->currentWeapon == weaponType) {
		printf("You cannot sell equipped weapon: %s.\n", weaponName);
		return -1;
	}
	printf("Selling weapon: %s\n", weaponName);

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
	if (hasArmor(inventory, armorType)) {
		printf("You already have the armor: %s\n", armorName);
		return -1;
	}
	printf("Purchasing armor: %s\n", armorName);

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

int sellArmor(Inventory* inventory, const Player* player, const ArmorType armorType, const char* armorName) {
	if (!hasArmor(inventory, armorType)) {
		printf("You have no armor: %s to sell.\n", armorName);
		return -1;
	}
	if (player->currentArmor == armorType) {
		printf("You cannot sell equipped armor: %s.\n", armorName);
		return -1;
	}
	printf("Selling armor: %s\n", armorName);

	int beforeGold = inventory->gold;
	int value = (int)(armorPriceArray[armorType] * SELL_RATE);

	addGold(inventory, value);
	removeArmor(inventory, armorType);

	printf("You have sold the armor: %s.\n", armorName);
	printf("%sG -> %sG (+%s)\n", formatNum(beforeGold), formatNum(inventory->gold), formatNum(value));

	return inventory->gold;
}
