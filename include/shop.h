#pragma once

#include "inventory.h"
#include "command.h"

void initShop();
void showShop();
int buyShop(Inventory* inventory, const Command *cmd);
int sellShop(Inventory* inventory, const Command *cmd);
