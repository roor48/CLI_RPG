#pragma once

struct Player;
struct Inventory;

/**
 * @brief 게임 데이터 저장
 * 
 * @param *player 저장할 데이터를 가져올 Player 포인터
 * @param *inventory 저장할 데이터를 가져올 Inventory 포인터
 * @param *filename 파일 이름
 * 
 * @return 성공 시 1, 실패 시 0
 */
int saveGame(const struct Player *player, const struct Inventory *inventory, const char* filename);

/**
 * @brief 게임 데이터 로드
 * 
 * @param *player 불러온 데이터를 저장할 Player 포인터
 * @param *inventory 불러온 데이터를 저장할 Inventory 포인터
 * @param *filename 파일 이름
 * 
 * @return 성공 시 1, 실패 시 0
 */
int loadGame(struct Player* player, struct Inventory* inventory, const char* filename);

/**
 * @brief 저장된 게임 목록 출력
 */
void listSavedGames();

