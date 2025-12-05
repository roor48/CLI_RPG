#include "../include/inventory.h"

#include "../include/constants.h"
#include "../include/item_stats.h"

#include <stdio.h>

void showInventory(const Inventory* inventory) {
	printf("Showing inventory...\n");

	printf("Gold: %d\n", inventory->gold);
	printf("Consumables:\n");
	for (int i = 0; i < MAX_CONSUMABLE_TYPES; i++) {
		if (hasConsumable(inventory, (ConsumableType)i)) {
			printf("  %s: %d\n", consumableNameArray[i], getConsumable(inventory, (ConsumableType)i));
		}
	}

	printf("Weapons:\n");
	for (int i = 0; i < MAX_WEAPON_TYPES; i++) {
		if (hasWeapon(inventory, (WeaponType)i)) {
			printf("  %s\n", weaponNameArray[i]);
		}
	}

	printf("Armors:\n");
	for (int i = 0; i < MAX_ARMOR_TYPES; i++) {
		if (hasArmor(inventory, (ArmorType)i)) {
			printf("  %s\n", armorNameArray[i]);
		}
	}
}

int getGold(const Inventory* inventory) {
	return inventory->gold;
}
int addGold(Inventory* inventory, const int amount) {

	int beforeGold = inventory->gold;
	inventory->gold += amount;
	printf("You got %d gold. (%dG -> %dG)\n", amount, beforeGold, inventory->gold);

	return inventory->gold;
}
// (10000G -> 10032G)
int removeGold(Inventory* inventory, const int amount) {
	if (inventory->gold < amount) {
		printf("ERROR in inventory.removeGold: inventory->gold < amount");
		return -1;
	}

	return inventory->gold -= amount;
}

int hasItem(const Inventory* inventory, const InventoryItem* inventoryItem) {
	switch (inventoryItem->tag) {
		case ITEMTAG_CONSUMABLE:
			return hasConsumable(inventory, inventoryItem->data.consumableType);

		case ITEMTAG_WEAPON:
			return hasWeapon(inventory, inventoryItem->data.weaponType);

		case ITEMTAG_ARMOR:
			return hasArmor(inventory, inventoryItem->data.armorType);

		case ITEMTAG_UNKNOWN:
		default:
			printf("Unknown item type\n");
			return -1;
	}
}

#pragma region Consumable
int hasConsumable(const Inventory* inventory, const ConsumableType consumableType) {
	if (consumableType == CONSUMABLE_UNKNOWN) {
		printf("Unknown item name\n");
		return -1;
	}

	return !!getConsumable(inventory, consumableType);
}
int getConsumable(const Inventory* inventory, const ConsumableType consumableType) {
	if (consumableType == CONSUMABLE_UNKNOWN) {
		printf("Unknown item name\n");
		return -1;
	}

	int result = inventory->consumables[consumableType];
	return result;
}
int addConsumable(Inventory* inventory, const ConsumableType consumableType, const int cnt) {
	if (consumableType == CONSUMABLE_UNKNOWN) {
		printf("Unknown item name\n");
		return -1;
	}

	inventory->consumables[consumableType] += cnt;
	return inventory->consumables[consumableType];
}
int removeConsumable(Inventory* inventory, const ConsumableType consumableType, const int cnt) {
	if (consumableType == CONSUMABLE_UNKNOWN) {
		printf("Unknown item name\n");
		return -1;
	}
	if (inventory->consumables[consumableType] < cnt) {
		printf("Amount is too big (have: %d, input: %d)", inventory->consumables[consumableType], cnt);
		return -2;
	}

	return inventory->consumables[consumableType] -= cnt;
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
