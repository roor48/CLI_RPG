#pragma once

#include "constants.h"

// 아이템 이름 배열
extern const char* consumableNameArray[MAX_CONSUMABLE_TYPES + 1];
extern const int consumablePriceArray[MAX_CONSUMABLE_TYPES + 1];

extern const char* weaponNameArray[MAX_WEAPON_TYPES + 1];
extern const int weaponPriceArray[MAX_WEAPON_TYPES + 1];

extern const char* armorNameArray[MAX_ARMOR_TYPES + 1];
extern const int armorPriceArray[MAX_ARMOR_TYPES + 1];

// 무기 대미지 배열
extern const int weaponDamageArray[MAX_WEAPON_TYPES + 1];

// 방어구 방어도 배열
extern const int armorDefenseArray[MAX_ARMOR_TYPES + 1];
