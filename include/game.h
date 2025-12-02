#pragma once

#include "player.h"
#include "inventory.h"
#include "constants.h"
#include "battle.h"

/*
 * @brief 게임 상태
 */
typedef enum GameState {
	STATE_INIT,
	STATE_RUNNING,
	STATE_FINISHED
} GameState;

/*
 * @brief 게임 씬
 */
typedef enum Scene {
	SCENE_UNKNOWN,
	SCENE_MAIN,
	SCENE_BATTLE
}Scene;

/*
 * @brief 게임 구조체
 * 
 * 게임의 현재 상태, 플레이어, 인벤토리 등 모든 데이터를 포함
 */
typedef struct Game {
	GameState state;
	Scene scene;
	Player player;
	Inventory inventory;
	Battle battle;
} Game;

/*
 * @brief 게임 시작
 * 
 * @return 게임 루프 횟수
 */
unsigned long long startGame();
