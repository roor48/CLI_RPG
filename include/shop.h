#pragma once

#include "inventory.h"
#include "command.h"

/**
 * @brief 상점 가격 초기화
 * 
 * 상점에서 판매 가능한 모든 아이템 가격 설정
 */
void initShop();

/**
 * @brief 구매 가능한 상점 아이템 및 가격 표시
 * 
 * 구매 가능한 모든 아이템의 목록과 가격 출력
 */
void showShop();

/**
 * @brief 상점에서 아이템 구매
 * 
 * @param *inventory 인벤토리의 포인터
 * @param *cmd 명령어
 * 
 * @return 구매 후 현재 골드량, 실패 시 -1
 */
int buyShop(Inventory* inventory, const Command *cmd);

/**
 * @brief 상점에 아이템 판매
 * 
 * @param *inventory 인벤토리의 포인터
 * @param *cmd 명령어
 * 
 * @return 판매 후 현재 골드량, 실패 시 -1
 */
int sellShop(Inventory* inventory, const Command *cmd);
