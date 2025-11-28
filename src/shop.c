#include "../include/shop.h"

#include "../include/constants.h"
#include "../include/inventory.h"
#include "../include/command.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SELL_RATE 0.5

void getItemTypeFromName(Command *cmd, ItemType *itemType, WeaponType *weaponType, ArmorType *armorType, int *amount);

int buyItem(Inventory* inventory, ItemType itemType, char* itemName, int amount);
int sellItem(Inventory* inventory, ItemType itemType, char* itemName, int amount);
int buyWeapon(Inventory* inventory, WeaponType itemType, char* itemName);
int sellWeapon(Inventory* inventory, WeaponType itemType, char* itemName);
int buyArmor(Inventory* inventory, ArmorType itemType, char* itemName);
int sellArmor(Inventory* inventory, ArmorType itemType, char* itemName);

int itemPrices[MAX_ITEM_TYPES], weaponPrices[MAX_WEAPON_TYPES], armorPrices[MAX_ARMOR_TYPES];

void toLowerCase(char *str) {
	for (int i = 0; str[i]; i++) {
		str[i] = tolower((unsigned char)str[i]);
	}
}

void getItemTypeFromName(Command *cmd, ItemType *itemType, WeaponType *weaponType, ArmorType *armorType, int *amount) {
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
	char itemName[MAX_ARG_LENGTH];
	strcpy_s(itemName, sizeof(itemName), cmd->arg1);
	itemName[MAX_ARG_LENGTH - 1] = '\0';
	toLowerCase(itemName);

	// char* 형태를 enum으로 변환
	// ITEM
	if (strcmp(itemName, "lowhealpotion") == 0 || strcmp(itemName, "low") == 0) {
		*itemType = ITEM_LOW_HEAL_POTION;
	}
	else if (strcmp(itemName, "healpotion") == 0 || strcmp(itemName, "heal") == 0) {
		*itemType = ITEM_HEAL_POTION;
	}
	else if (strcmp(itemName, "highhealpotion") == 0 || strcmp(itemName, "high") == 0) {
		*itemType = ITEM_HIGH_HEAL_POTION;
	}
	// WEAPON
	else if (strcmp(itemName, "coopersword") == 0 || strcmp(itemName, "cooper") == 0) {
		*weaponType = WEAPON_COOPER_SWORD;
	}
	else if (strcmp(itemName, "ironsword") == 0 || strcmp(itemName, "iron") == 0) {
		*weaponType = WEAPON_IRON_SWORD;
	}
	// ARMOR
	else if (strcmp(itemName, "woodchestplate") == 0 || strcmp(itemName, "wood") == 0) {
		*armorType = ARMOR_WOOD_CHESTPLATE;
	}
	// UNKNOWN
	else {
		printf("Unknown item: %s\n", cmd->arg1);
		return;
	}
}

void initShop() {
	// 아이템 가격 설정
	itemPrices[ITEM_LOW_HEAL_POTION] = 10;
	itemPrices[ITEM_HEAL_POTION] = 25;
	itemPrices[ITEM_HIGH_HEAL_POTION] = 50;
	// 무기 가격 설정
	weaponPrices[WEAPON_COOPER_SWORD] = 100;
	weaponPrices[WEAPON_IRON_SWORD] = 200;
	// 방어구 가격 설정
	armorPrices[ARMOR_WOOD_CHESTPLATE] = 150;
}

void showShop() {
	printf("Welcome to the shop! Here are the items available for purchase:\n");
	printf("1. LowHealPotion - %d Gold\n", itemPrices[ITEM_LOW_HEAL_POTION]);
	printf("2. HealPotion - %d Gold\n", itemPrices[ITEM_HEAL_POTION]);
	printf("3. HighHealPotion - %d Gold\n", itemPrices[ITEM_HIGH_HEAL_POTION]);
	printf("4. CooperSword -  %d Gold\n", weaponPrices[WEAPON_COOPER_SWORD]);
	printf("5. IronSword -  %d Gold\n", weaponPrices[WEAPON_IRON_SWORD]);
	printf("6. WoodChestplate -  %d Gold\n", armorPrices[ARMOR_WOOD_CHESTPLATE]);
	printf("Type 'buy [item name] [amount]' to purchase an item.\n");
}

void buyShop(Inventory *inventory, Command *cmd) {
	ItemType itemType = ITEM_UNKNOWN;
	WeaponType weaponType = WEAPON_UNKNOWN;
	ArmorType armorType = ARMOR_UNKNOWN;
	int amount = 1;

	getItemTypeFromName(cmd, &itemType, &weaponType, &armorType, &amount);

	// 아이템 구매
	if (itemType != ITEM_UNKNOWN) {
		buyItem(inventory, itemType, cmd->arg1, amount);
	}
	else if (weaponType != WEAPON_UNKNOWN) {
		buyWeapon(inventory, weaponType, cmd->arg1);
	}
	else if (armorType != ARMOR_UNKNOWN) {
		buyArmor(inventory, armorType, cmd->arg1);
	}
}

void sellShop(Inventory* inventory, Command *cmd) {
	ItemType itemType = ITEM_UNKNOWN;
	WeaponType weaponType = WEAPON_UNKNOWN;
	ArmorType armorType = ARMOR_UNKNOWN;
	int amount = 1;

	getItemTypeFromName(cmd, &itemType, &weaponType, &armorType, &amount);

	// 아이템 판매
	if (itemType != ITEM_UNKNOWN) {
		sellItem(inventory, itemType, cmd->arg1, amount);
	}
	else if (weaponType != WEAPON_UNKNOWN) {
		sellWeapon(inventory, weaponType, cmd->arg1);
	}
	else if (armorType != ARMOR_UNKNOWN) {
		sellArmor(inventory, armorType, cmd->arg1);
	}
}

int buyItem(Inventory* inventory, ItemType itemType, char *itemName, int amount) {
	printf("Purchasing %d x %s\n", amount, itemName);

	int beforeGold = inventory->gold;
	int value = itemPrices[itemType] * amount;

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

int sellItem(Inventory* inventory, ItemType itemType, char *itemName, int amount) {
	printf("Selling %d x %s\n", amount, itemName);

	int beforeGold = inventory->gold;
	int value = itemPrices[itemType] * amount * SELL_RATE;

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
int buyWeapon(Inventory* inventory, WeaponType weaponType, char *itemName) {
	printf("Purchasing weapon: %s\n", itemName);

	int beforeGold = inventory->gold;
	int value = weaponPrices[weaponType];

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

int sellWeapon(Inventory* inventory, WeaponType weaponType, char *itemName) {
	printf("Selling weapon: %s\n", itemName);

	if (!hasWeapon(inventory, weaponType)) {
		printf("You have no weapon: %s to sell.\n", itemName);
		return -1;
	}

	int beforeGold = inventory->gold;
	int value = weaponPrices[weaponType] * SELL_RATE;

	addGold(inventory, value);
	removeWeapon(inventory, weaponType);

	printf("You have sold the weapon: %s.\n", itemName);
	printf("%dG -> %dG (+%d)\n", beforeGold, inventory->gold, value);

}

// Armor
int buyArmor(Inventory* inventory, ArmorType armorType, char* itemName) {
	printf("Purchasing armor: %s\n", itemName);

	int beforeGold = inventory->gold;
	int value = armorPrices[armorType];

	if (beforeGold < value) {
		printf("Not enough gold to purchase %s\n", itemName);
		return -1;
	}

	removeGold(inventory, value);
	addArmor(inventory, armorType);

	printf("You have purchased the armor: %s.\n", itemName);
	printf("%dG -> %dG (-%d)\n", beforeGold, inventory->gold, value);
}

int sellArmor(Inventory* inventory, ArmorType armorType, char* itemName) {
	printf("Selling armor: %s\n", itemName);

	if (!hasArmor(inventory, armorType)) {
		printf("You have no armor: %s to sell.\n", itemName);
		return -1;
	}

	int beforeGold = inventory->gold;
	int value = armorPrices[armorType] * SELL_RATE;

	addGold(inventory, value);
	removeArmor(inventory, armorType);

	printf("You have sold the armor: %s.\n", itemName);
	printf("%dG -> %dG (+%d)\n", beforeGold, inventory->gold, value);
}
