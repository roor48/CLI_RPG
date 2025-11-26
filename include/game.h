#pragma once
#include "player.h"
#include "inventory.h"
#include "constants.h"

typedef enum {
	STATE_INIT,
	STATE_RUNNING,
	STATE_PAUSED,
	STATE_FINISHED
} GameState;

typedef struct {
	GameState state;
	Player player;
	Inventory inventory;
} Game;

unsigned long long startGame();
