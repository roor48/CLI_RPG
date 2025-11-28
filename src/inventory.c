#include "../include/inventory.h"

#include <stdio.h>

void showInventory(Inventory* inventory) {
	printf("Showing inventory...\n");

	printf("Gold: %d\n", inventory->gold);
	printf("Items:\n");
	if (hasItem(inventory, ITEM_LOW_HEAL_POTION)) {
		printf("  LowHealPotion: %d\n", getItem(inventory, ITEM_LOW_HEAL_POTION));
	}
	if (hasItem(inventory, ITEM_HEAL_POTION)) {
		printf("  HealPotion: %d\n", getItem(inventory, ITEM_HEAL_POTION));
	}
	if (hasItem(inventory, ITEM_HIGH_HEAL_POTION)) {
		printf("  HighHealPotion: %d\n", getItem(inventory, ITEM_HIGH_HEAL_POTION));
	}

	printf("Weapons:\n");
	if (hasWeapon(inventory, WEAPON_COOPER_SWORD)) {
		printf("  CooperSword\n");
	}
	if (hasWeapon(inventory, WEAPON_IRON_SWORD)) {
		printf("  IronSword\n");
	}

	printf("Armors:\n");
	if (hasArmor(inventory, ARMOR_WOOD_CHESTPLATE)) {
		printf(" WoodChestplate\n");
	}
}

int addGold(Inventory* inventory, int amount) {
	return inventory->gold += amount;
}

int removeGold(Inventory* inventory, int amount) {
	if (inventory->gold < amount) {
		printf("ERROR in inventory.removeGold: inventory->gold < amount");
		return -1;
	}

	return inventory->gold -= amount;
}

#pragma region Item
int hasItem(Inventory* inventory, ItemType itemType) {
	if (itemType == ITEM_UNKNOWN) {
		printf("Unknown item name\n");
		return -1;
	}

	return !!getItem(inventory, itemType);
}

int getItem(Inventory* inventory, ItemType itemType) {
	if (itemType == ITEM_UNKNOWN) {
		printf("Unknown item name\n");
		return -1;
	}

	int result = inventory->items[itemType];
	return result;
}

// 아이템 추가
int addItem(Inventory* inventory, ItemType itemType, int cnt) {
	if (itemType == ITEM_UNKNOWN) {
		printf("Unknown item name\n");
		return -1;
	}

	inventory->items[itemType] += cnt;
	return inventory->items[itemType];
}

// 아이템 제거
int removeItem(Inventory* inventory, ItemType itemType, int cnt) {
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
int hasWeapon(Inventory* inventory, WeaponType weaponType) {
	if (weaponType == WEAPON_UNKNOWN) {
		printf("Unknown weapon name\n");
		return -1;
	}

	return inventory->weapons[weaponType];
}

int addWeapon(Inventory* inventory, WeaponType weaponType) {
	if (weaponType == WEAPON_UNKNOWN) {
		printf("Unknown weapon name\n");
		return -1;
	}

	return inventory->weapons[weaponType] = 1;
}
int removeWeapon(Inventory* inventory, WeaponType weaponType) {
	if (weaponType == WEAPON_UNKNOWN) {
		printf("Unknown weapon name\n");
		return -1;
	}

	return inventory->weapons[weaponType] = 0;
}

#pragma endregion


#pragma region Armor
int hasArmor(Inventory* inventory, ArmorType armorType) {
	if (armorType == ARMOR_UNKNOWN) {
		printf("Unknown armor name\n");
		return -1;
	}

	return inventory->armors[armorType];
}
int addArmor(Inventory* inventory, ArmorType armorType) {
	if (armorType == ARMOR_UNKNOWN) {
		printf("Unknown armor name\n");
		return -1;
	}

	return inventory->armors[armorType] = 1;
}
int removeArmor(Inventory* inventory, ArmorType armorType) {
	if (armorType == ARMOR_UNKNOWN) {
		printf("Unknown armor name\n");
		return -1;
	}

	return inventory->armors[armorType] = 0;
}

#pragma endregion

