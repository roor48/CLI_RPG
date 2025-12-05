#pragma once

#include "constants.h"

struct Command;
struct InventoryItem;

// 아이템 이름 배열
extern const char* consumableNameArray[MAX_CONSUMABLE_TYPES];
extern const int consumablePriceArray[MAX_CONSUMABLE_TYPES];

extern const char* weaponNameArray[MAX_WEAPON_TYPES];
extern const int weaponPriceArray[MAX_WEAPON_TYPES];

extern const char* armorNameArray[MAX_ARMOR_TYPES];
extern const int armorPriceArray[MAX_ARMOR_TYPES];

// 무기 대미지 배열
extern const int weaponDamageArray[MAX_WEAPON_TYPES];

// 방어구 방어도 배열
extern const int armorDefenseArray[MAX_ARMOR_TYPES];

/*
 * @brief char* 형식을 InventoryItem 타입으로 변환
 *
 * @param *cmd 명령어
 * @param *inventoryItem 변환 값을 저장할 포인터
 */
void getItemTypeFromName(const struct Command* cmd, struct InventoryItem* inventoryItem);
