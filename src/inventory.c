#include "../include/inventory.h"

#include <stdio.h>

#pragma region Item
int hasItem(Inventory* inventory, ItemType itemType) {
	int have = -1;
	switch (itemType) {
		case ITEM_LOW_HEAL_POTION:
			have = !!inventory->lowHealPotion;
			break;

		case ITEM_HEAL_POTION:
			have = !!inventory->healPotion;
			break;

		case ITEM_HIGH_HEAL_POTION:
			have = !!inventory->highHealPotion;
			break;

		case ITEM_UNKNOWN:
		default:
			printf("Unknown item name\n");
			have = -1;
			break;
	}

	return have;
}

// ¾ÆÀÌÅÛ Ãß°¡
int addItem(Inventory* inventory, ItemType itemType, int cnt) {
	int result = 0;
	switch (itemType) {
		case ITEM_LOW_HEAL_POTION:
			addLowHealPotion(inventory, cnt);
			result = inventory->lowHealPotion;
			break;

		case ITEM_HEAL_POTION:
			addHealPotion(inventory, cnt);
			result = inventory->healPotion;
			break;

		case ITEM_HIGH_HEAL_POTION:
			addHighHealPotion(inventory, cnt);
			result = inventory->highHealPotion;
			break;

		case ITEM_UNKNOWN:
		default:
			result = -1;
			printf("Unknown item name\n");
			break;
	}

	return result;
}

// ¾ÆÀÌÅÛ Á¦°Å
int removeItem(Inventory* inventory, ItemType itemType, int cnt) {
	int result = 0;
	switch (itemType) {
		case ITEM_LOW_HEAL_POTION:
			removeLowHealPotion(inventory, cnt);
			result = inventory->lowHealPotion;
			break;

		case ITEM_HEAL_POTION:
			removeHealPotion(inventory, cnt);
			result = inventory->healPotion;
			break;

		case ITEM_HIGH_HEAL_POTION:
			removeHighHealPotion(inventory, cnt);
			result = inventory->highHealPotion;
			break;

		case ITEM_UNKNOWN:
		default:
			result = -1;
			printf("Unknown item name\n");
			break;
	}

	return result;
}

// ¾ÆÀÌÅÛ Ãß°¡
int addLowHealPotion(Inventory* inventory, int cnt) {
	return inventory->lowHealPotion += cnt;
}
int addHealPotion(Inventory* inventory, int cnt) {
	return inventory->healPotion += cnt;
}
int addHighHealPotion(Inventory* inventory, int cnt) {
	return inventory->highHealPotion += cnt;
}

// ¾ÆÀÌÅÛ Á¦°Å
int removeLowHealPotion(Inventory* inventory, int cnt) {
	inventory->lowHealPotion -= cnt;
	if (inventory->lowHealPotion < 0) {
		inventory->lowHealPotion = 0;
	}

	return inventory->lowHealPotion;
}
int removeHealPotion(Inventory* inventory, int cnt) {
	inventory->healPotion -= cnt;
	if (inventory->healPotion < 0) {
		inventory->healPotion = 0;
	}

	return inventory->healPotion;
}
int removeHighHealPotion(Inventory* inventory, int cnt) {
	inventory->highHealPotion -= cnt;
	if (inventory->highHealPotion < 0) {
		inventory->highHealPotion = 0;
	}

	return inventory->highHealPotion;
}
#pragma endregion


#pragma region Weapon
int hasWeapon(Inventory* inventory, WeaponType weaponType) {
	int have = -1;
	switch (weaponType) {
	case WEAPON_COOPER_SWORD:
		have = inventory->cooperSword;
		break;
	case WEAPON_IRON_SWORD:
		have = inventory->ironSword;
		break;

	case WEAPON_UNKNOWN:
	default:
		have = -1;
		break;
	}

	return have;
}
int getWeapon(Inventory* inventory, WeaponType weaponType) {
	int have = 0;
	switch (weaponType) {
	case WEAPON_COOPER_SWORD:
		have = getCooperSword(inventory);
		break;

	case WEAPON_IRON_SWORD:
		have = getIronSword(inventory);
		break;

	case WEAPON_UNKNOWN:
	default:
		have = -1;
		break;
	}
}
int removeWeapon(Inventory* inventory, WeaponType weaponType) {
	int have = 0;
	switch (weaponType) {
		case WEAPON_COOPER_SWORD:
			have = removeCooperSword(inventory);
			break;
		case WEAPON_IRON_SWORD:
			have = removeIronSword(inventory);
			break;

		case WEAPON_UNKNOWN:
		default:
			have = -1;
			break;
	}

	return have;
}

// ¹«±â È¹µæ
int getCooperSword(Inventory* inventory) {
	return inventory->cooperSword = 1;
}
int getIronSword(Inventory* inventory) {
	return inventory->ironSword = 1;
}

// ¹«±â Á¦°Å
int removeCooperSword(Inventory* inventory) {
	return inventory->cooperSword = 0;
}
int removeIronSword(Inventory* inventory) {
	return inventory->ironSword = 0;
}

#pragma endregion


#pragma region Armor
int hasArmor(Inventory* inventory, ArmorType armorType) {
	int have = -1;
	switch (armorType) {
		case ARMOR_WOOD_CHESTPLATE:
			have = inventory->woodChestplate;
			break;

		case ARMOR_UNKNOWN:
		default:
			have = -1;
			break;
	}

	return have;
}
int getArmor(Inventory* inventory, ArmorType armorType) {
	int have = -1;
	switch (armorType) {
	case ARMOR_WOOD_CHESTPLATE:
		have = getWoodChestplate(inventory);
		break;

	case ARMOR_UNKNOWN:
	default:
		have = -1;
		break;
	}

	return have;
}
int removeArmor(Inventory* inventory, ArmorType armorType) {
	int have = -1;
	switch (armorType) {
	case ARMOR_WOOD_CHESTPLATE:
		have = removeWoodChestplate(inventory);
		break;

	case ARMOR_UNKNOWN:
	default:
		have = -1;
		break;
	}

	return have;
}

// °©¿Ê È¹µæ
int getWoodChestplate(Inventory* inventory) {
	return inventory->woodChestplate = 1;
}

// °©¿Ê Á¦°Å
int removeWoodChestplate(Inventory* inventory) {
	return inventory->woodChestplate = 0;
}

#pragma endregion

