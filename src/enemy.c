#include "../include/enemy.h"

#include "../include/player.h"

#include <stdio.h>

int onHitEnemy(Enemy* enemy, const int dmg) {
	enemy->health -= dmg;
	if (enemy->health < 0) {
		enemy->health = 0;
	}

	printf("Attacked %s with %d damage. Enemy health: %d/%d\n",
		enemy->name,
		dmg,
		enemy->health,
		enemy->maxHealth);

	return enemy->health;
}

int attackPlayer(const Enemy* enemy, Player* player) {
	return onHitPlayer(player, enemy);
}
