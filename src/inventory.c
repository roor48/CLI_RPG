#include "../include/inventory.h"

#include "../include/constants.h"
#include "../include/shop.h"

#include <stdio.h>

void showInventory(const Inventory* inventory) {
	printf("Showing inventory...\n");

	printf("Gold: %d\n", inventory->gold);
	printf("Items:\n");
	for (int i = 1; i <= MAX_ITEM_TYPES; i++) {
		if (hasItem(inventory, (ItemType)i)) {
			printf("  %s: %d\n", itemNameArray[i], getItem(inventory, (ItemType)i));
		}
	}

	printf("Weapons:\n");
	for (int i = 1; i <= MAX_WEAPON_TYPES; i++) {
		if (hasWeapon(inventory, (WeaponType)i)) {
			printf("  %s\n", weaponNameArray[i]);
		}
	}

	printf("Armors:\n");
	for (int i = 1; i <= MAX_ARMOR_TYPES; i++) {
		if (hasArmor(inventory, (ArmorType)i)) {
			printf("  %s\n", armorNameArray[i]);
		}
	}
}

int getGold(const Inventory* inventory) {
	return inventory->gold;
}
int addGold(Inventory* inventory, const int amount) {
	return inventory->gold += amount;
}
int removeGold(Inventory* inventory, const int amount) {
	if (inventory->gold < amount) {
		printf("ERROR in inventory.removeGold: inventory->gold < amount");
		return -1;
	}

	return inventory->gold -= amount;
}

#pragma region Item
int hasItem(const Inventory* inventory, const ItemType itemType) {
	if (itemType == ITEM_UNKNOWN) {
		printf("Unknown item name\n");
		return -1;
	}

	return !!getItem(inventory, itemType);
}
int getItem(const Inventory* inventory, const ItemType itemType) {
	if (itemType == ITEM_UNKNOWN) {
		printf("Unknown item name\n");
		return -1;
	}

	int result = inventory->items[itemType];
	return result;
}
int addItem(Inventory* inventory, const ItemType itemType, const int cnt) {
	if (itemType == ITEM_UNKNOWN) {
		printf("Unknown item name\n");
		return -1;
	}

	inventory->items[itemType] += cnt;
	return inventory->items[itemType];
}
int removeItem(Inventory* inventory, const ItemType itemType, const int cnt) {
	if (itemType == ITEM_UNKNOWN) {
		printf("Unknown item name\n");
		return -1;
	}
	if (inventory->items[itemType] < cnt) {
		printf("Amount is too big (have: %d, input: %d)", inventory->items[itemType], cnt);
		return -2;
	}

	return inventory->items[itemType] -= cnt;
}
#pragma endregion


#pragma region Weapon
int hasWeapon(const Inventory* inventory, const WeaponType weaponType) {
	if (weaponType == WEAPON_UNKNOWN) {
		printf("Unknown weapon name\n");
		return -1;
	}

	return inventory->weapons[weaponType];
}
int addWeapon(Inventory* inventory, const WeaponType weaponType) {
	if (weaponType == WEAPON_UNKNOWN) {
		printf("Unknown weapon name\n");
		return -1;
	}

	return inventory->weapons[weaponType] = 1;
}
int removeWeapon(Inventory* inventory, const WeaponType weaponType) {
	if (weaponType == WEAPON_UNKNOWN) {
		printf("Unknown weapon name\n");
		return -1;
	}

	return inventory->weapons[weaponType] = 0;
}
#pragma endregion


#pragma region Armor
int hasArmor(const Inventory* inventory, const ArmorType armorType) {
	if (armorType == ARMOR_UNKNOWN) {
		printf("Unknown armor name\n");
		return -1;
	}

	return inventory->armors[armorType];
}
int addArmor(Inventory* inventory, const ArmorType armorType) {
	if (armorType == ARMOR_UNKNOWN) {
		printf("Unknown armor name\n");
		return -1;
	}

	return inventory->armors[armorType] = 1;
}
int removeArmor(Inventory* inventory, const ArmorType armorType) {
	if (armorType == ARMOR_UNKNOWN) {
		printf("Unknown armor name\n");
		return -1;
	}

	return inventory->armors[armorType] = 0;
}
#pragma endregion
