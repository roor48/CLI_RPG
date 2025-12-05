#include "../include/enemy.h"

#include "../include/player.h"
#include "../include/string_utils.h"

#include <stdio.h>

int onHitEnemy(Enemy* enemy, const int dmg) {
	enemy->health -= dmg;
	if (enemy->health < 0) {
		enemy->health = 0;
	}

	printf("Attacked %s with %s damage. Enemy health: %s/%s\n",
		enemy->name,
		formatNum(dmg),
		formatNum(enemy->health),
		formatNum(enemy->maxHealth));

	return enemy->health;
}

int attackPlayer(const Enemy* enemy, Player* player) {
	return onHitPlayer(player, enemy);
}
