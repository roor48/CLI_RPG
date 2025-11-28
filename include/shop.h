#pragma once

#include "inventory.h"
#include "command.h"

void initShop();
void showShop();
void buyShop(Inventory* inventory, Command *cmd);
void sellShop(Inventory* inventory, Command *cmd);
