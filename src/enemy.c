#include "../include/enemy.h"

#include "../include/player.h"

#include <stdio.h>

int onHitEnemy(Enemy* enemy, const int dmg) {
	enemy->health -= dmg;
	if (enemy->health < 0) {
		enemy->health = 0;
	}

	return enemy->health;
}

int attackPlayer(const Enemy* enemy, Player* player) {
	player->health -= enemy->damage;
	if (player->health < 0) {
		player->health = 0;
	}

	printf("%s attacked you with %d damage. Your health: %d\n",
		enemy->name,
		enemy->damage,
		player->health);

	return player->health;
}
