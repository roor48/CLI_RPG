#pragma once
#include "player.h"
#include "constants.h"

enum GAME_SATE {
	STATE_INIT,
	STATE_RUNNING,
	STATE_PAUSED,
	STATE_FINISHED
};

typedef struct {
	enum GAME_SATE state;
	Player player;
} Game;

unsigned long long startGame();
