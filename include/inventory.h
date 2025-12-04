#pragma once

#include "constants.h"

/**
 * @brief 아이템 타입
 */
typedef enum ItemType {
	ITEM_UNKNOWN = 0,
	ITEM_LOW_HEAL_POTION = 1,
	ITEM_HEAL_POTION = 2,
	ITEM_HIGH_HEAL_POTION = 3
} ItemType;

/**
 * @brief 무기 타입
 */
typedef enum WeaponType {
	WEAPON_UNKNOWN = 0,
	WEAPON_COOPER_SWORD = 1,
	WEAPON_IRON_SWORD = 2
} WeaponType;

/**
 * @brief 방어구 타입
 */
typedef enum ArmorType {
	ARMOR_UNKNOWN = 0,
	ARMOR_WOOD_CHESTPLATE = 1,
} ArmorType;

/**
 * @brief 인벤토리 아이템 태그
 * 
 * Union에서 어떤 타입이 유효한지 구분
 */
typedef enum ItemTag {
	ITEMTAG_UNKNOWN = 0,
	ITEMTAG_ITEM = 1,
	ITEMTAG_WEAPON = 2,
	ITEMTAG_ARMOR = 3
} ItemTag;

/**
 * @brief 인벤토리 아이템 Union
 * 
 * 아이템, 무기, 방어구 중 하나의 타입을 저장
 */
typedef union InventoryItemUnion {
	ItemType itemType;
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
	int gold;							// 골드
	int items[MAX_ITEM_TYPES + 1];		// 아이템 (수량)
	int weapons[MAX_WEAPON_TYPES + 1];	// 무기 (소유 여부)
	int armors[MAX_ARMOR_TYPES + 1];	// 방어구 (소유 여부)
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

/**
 * @brief 아이템 소유 여부 확인
 * 
 * @param *inventory 인벤토리 포인터
 * @param itemType 아이템 타입
 * 
 * @return 소유 시 1, 미소유 시 0, 오류 시 -1
 */
int hasItem(const Inventory *inventory, const ItemType itemType);

/**
 * @brief 아이템 수량 조회
 * 
 * @param *inventory 인벤토리 포인터
 * @param itemType 아이템 타입
 * 
 * @return 아이템 수량, 오류 시 -1
 */
int getItem(const Inventory* inventory, const ItemType itemType);

/**
 * @brief 아이템 추가
 * 
 * @param *inventory 인벤토리 포인터
 * @param itemType 아이템 타입
 * @param cnt 추가할 수량
 * 
 * @return 추가 후 수량, 오류 시 -1
 */
int addItem(Inventory* inventory, const ItemType itemType, const int cnt);

/**
 * @brief 아이템 제거
 * 
 * @param *inventory 인벤토리 포인터
 * @param itemType 아이템 타입
 * @param cnt 제거할 수량
 * 
 * @return 제거 후 수량, 오류 시 -1 또는 -2
 */
int removeItem(Inventory* inventory, const ItemType itemType, const int cnt);

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
