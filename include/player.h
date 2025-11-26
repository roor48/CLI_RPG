#pragma once
typedef struct {
	int health;
	int level;
} Player;

void attackEnemy(Player* player, const char* skill, const char* target);