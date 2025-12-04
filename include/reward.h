#pragma once

struct Inventory;
struct Player;

void giveWinReward(struct Inventory *inventory, struct Player *player);
void giveLoseReward(struct Inventory* inventory, struct Player* player);

