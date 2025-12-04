#include "../include/reward.h"

#include <stdlib.h>

#include "../include/inventory.h"
#include "../include/player.h"

void giveReward(Inventory* inventory, Player* player, const int gold, const int exp);

void giveWinReward(Inventory* inventory, Player* player) {
	giveReward(inventory, player, 30, 50);
}

void giveLoseReward(Inventory* inventory, Player* player) {
	giveReward(inventory, player, 7, 16);
}

void giveReward(Inventory* inventory, Player* player, const int gold, const int exp) {
	addGold(inventory, gold);
	givePlayerExp(player, exp);
}
