#include "../include/enemy.h"

#include "../include/player.h"


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

	return player->health;
}
