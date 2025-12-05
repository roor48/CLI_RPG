#pragma once

#include "constants.h"

/**
 * @brief 소모템 타입
 */
typedef enum ConsumableType {
	CONSUMABLE_LOW_HEAL_POTION = 0,
	CONSUMABLE_HEAL_POTION = 1,
	CONSUMABLE_HIGH_HEAL_POTION = 2,

	CONSUMABLE_UNKNOWN
} ConsumableType;

/**
 * @brief 무기 타입
 */
typedef enum WeaponType {
	WEAPON_NONE = 0,
	WEAPON_COOPER_SWORD = 1,
	WEAPON_IRON_SWORD = 2,

	WEAPON_UNKNOWN
} WeaponType;

/**
 * @brief 방어구 타입
 */
typedef enum ArmorType {
	ARMOR_NONE = 0,
	ARMOR_WOOD_CHESTPLATE = 1,

	ARMOR_UNKNOWN
} ArmorType;

/**
 * @brief 인벤토리 아이템 태그
 * 
 * Union에서 어떤 타입이 유효한지 구분
 */
typedef enum ItemTag {
	ITEMTAG_CONSUMABLE = 0,
	ITEMTAG_WEAPON = 1,
	ITEMTAG_ARMOR = 2,

	ITEMTAG_UNKNOWN
} ItemTag;

/**
 * @brief 인벤토리 아이템 Union
 * 
 * 소모템, 무기, 방어구 중 하나의 타입을 저장
 */
typedef union InventoryItemUnion {
	ConsumableType consumableType;
	WeaponType weaponType;
	ArmorType armorType;
} InventoryItemUnion;

/**
 * @brief 인벤토리 아이템
 * 
 * 태그와 실제 데이터를 함께 저장하는 Tagged Union
 */
typedef struct InventoryItem {
	ItemTag tag;
	InventoryItemUnion data;
} InventoryItem;

/**
 * @brief 인벤토리
 * 
 * 플레이어의 소지품을 관리하는 구조체
 */
typedef struct Inventory {
	int gold;									// 골드
	int consumables[MAX_CONSUMABLE_TYPES];	// 소모템 (수량)
	int weapons[MAX_WEAPON_TYPES];			// 무기 (소유 여부)
	int armors[MAX_ARMOR_TYPES];			// 방어구 (소유 여부)
} Inventory;

/**
 * @brief 인벤토리 내용 출력
 * 
 * @param *inventory 인벤토리 포인터
 */
void showInventory(const Inventory* inventory);

/**
 * @brief 골드 조회
 * 
 * @param *inventory 인벤토리 포인터
 * @return 현재 골드량
 */
int getGold(const Inventory* inventory);

/**
 * @brief 골드 추가
 * 
 * @param *inventory 인벤토리 포인터
 * @param amount 추가할 골드량
 * 
 * @return 추가 후 골드량
 */
int addGold(Inventory* inventory, const int amount);

/**
 * @brief 골드 제거
 * 
 * @param *inventory 인벤토리 포인터
 * @param amount 제거할 골드량
 * 
 * @return 제거 후 골드량, 실패 시 -1
 */
int removeGold(Inventory* inventory, const int amount);

/*
 * @brief 아이템 소유 여부 확인
 * 
 * @param *inventory Inventory 포인터
 * @param *inventoryItem InventoryItem 포인터
 * 
 * @return 소유 시 1, 미소유 시 0, 오류 시 -1
 */
int hasItem(const Inventory* inventory, const InventoryItem* inventoryItem);

/**
 * @brief 소모템 소유 여부 확인
 * 
 * @param *inventory 인벤토리 포인터
 * @param consumableType 소모템 타입
 * 
 * @return 소유 시 1, 미소유 시 0, 오류 시 -1
 */
int hasConsumable(const Inventory* inventory, const ConsumableType consumableType);

/**
 * @brief 소모템 수량 조회
 *
 * @param *inventory 인벤토리 포인터
 * @param consumableType 소모템 타입
 * 
 * @return 아이템 수량, 오류 시 -1
 */
int getConsumable(const Inventory* inventory, const ConsumableType consumableType);

/**
 * @brief 소모템 추가
 * 
 * @param *inventory 인벤토리 포인터
 * @param consumableType 소모템 타입
 * @param cnt 추가할 수량
 * 
 * @return 추가 후 수량, 오류 시 -1
 */
int addConsumable(Inventory* inventory, const ConsumableType consumableType, const int cnt);

/**
 * @brief 소모템 제거
 *
 * @param *inventory 인벤토리 포인터
 * @param consumableType 소모템 타입
 * @param cnt 제거할 수량
 *
 * @return 제거 후 수량, 오류 시 -1 또는 -2
 */
int removeConsumable(Inventory* inventory, const ConsumableType consumableType, const int cnt);

/**
 * @brief 무기 소유 여부 확인
 * 
 * @param *inventory 인벤토리 포인터
 * @param weaponType 무기 타입
 * 
 * @return 소유 시 1, 미소유 시 0, 오류 시 -1
 */
int hasWeapon(const Inventory *inventory, const WeaponType weaponType);

/**
 * @brief 무기 추가
 * 
 * @param *inventory 인벤토리 포인터
 * @param weaponType 무기 타입
 * 
 * @return 성공 시 1, 오류 시 -1
 */
int addWeapon(Inventory *inventory, const WeaponType weaponType);

/**
 * @brief 무기 제거
 * 
 * @param *inventory 인벤토리 포인터
 * @param weaponType 무기 타입
 * 
 * @return 성공 시 0, 오류 시 -1
 */
int removeWeapon(Inventory *inventory, const WeaponType weaponType);

/**
 * @brief 방어구 소유 여부 확인
 * 
 * @param *inventory 인벤토리 포인터
 * @param armorType 방어구 타입
 * 
 * @return 소유 시 1, 미소유 시 0, 오류 시 -1
 */
int hasArmor(const Inventory *inventory, const ArmorType armorType);

/**
 * @brief 방어구 추가
 * 
 * @param *inventory 인벤토리 포인터
 * @param armorType 방어구 타입
 * 
 * @return 성공 시 1, 오류 시 -1
 */
int addArmor(Inventory *inventory, const ArmorType armorType);

/**
 * @brief 방어구 제거
 * 
 * @param *inventory 인벤토리 포인터
 * @param armorType 방어구 타입
 * 
 * @return 성공 시 0, 오류 시 -1
 */
int removeArmor(Inventory *inventory, const ArmorType armorType);
