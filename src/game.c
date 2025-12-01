#include "../include/game.h"

#include <stdio.h>
#include <string.h>

#include "../include/input.h"
#include "../include/command.h"
#include "../include/player.h"
#include "../include/inventory.h"
#include "../include/shop.h"

void initGame();
void executeCommand(const Command* cmd);

void help();
void battle();
void attack(const Command* cmd);
void attackList();
void inventory();
void shop();
void buy(const Command* cmd);
void sell(const Command* cmd);
void equip(const Command* cmd);
void useItem(const Command* cmd);
void run();
void save(const Command* cmd);
void load(const Command* cmd);
void saveList();
void quit();


Game game;
unsigned long long startGame() {
	initGame();

	char query[MAX_INPUT_LENGTH];

	game.state = STATE_RUNNING;
	printf("Game started! Type 'help' for commands.\n");

	unsigned long long loopCnt = 0;
	while (game.state != STATE_FINISHED) {
		loopCnt++;

		size_t len = getInput(query);

		if (len == 0) {
			continue;
		}

		Command cmd = parseCommand(query);
		executeCommand(&cmd);
	}

	return loopCnt;
}

void initGame() {
	Player player = (Player){ .health = 100, .level = 1 };
	Inventory inventory = (Inventory){ .gold = 10000 };

	game = (Game){ .state = STATE_INIT, .player = player, .inventory = inventory };
	initShop();
}

void executeCommand(const Command* cmd) {
	switch (cmd->type) {
	case CMD_HELP:
		help();
		break;

		// battle
	case CMD_BATTLE:
		battle();
		break;

	case CMD_ATTACK:
		attack(cmd);
		break;

	case CMD_ATTACKLIST:
		attackList();
		break;

	case CMD_USEITEM:
		useItem(cmd);
		break;

	case CMD_RUN:
		run();
		break;

		// shop
	case CMD_SHOP:
		shop(cmd);
		break;

	case CMD_BUY:
		buy(cmd);
		break;

	case CMD_SELL:
		sell(cmd);
		break;

		// inventory
	case CMD_INVENTORY:
		inventory();
		break;
	case CMD_EQUIP:
		equip(cmd);
		break;

		// save/load
	case CMD_SAVE:
		save(cmd);
		break;

	case CMD_SAVELIST:
		saveList();
		break;

	case CMD_LOAD:
		load(cmd);
		break;


		// quit
	case CMD_QUIT:
		quit();
		break;

		// error
	case CMD_ERROR:
		printf("%s\n", cmd->message);
		break;

	case CMD_UNKNOWN:
	default:
		printf("Unknown command. Type 'help' for available commands.\n");
		break;
	}
}

void help() {
	puts("Available commands:");
	puts("  * help - Show this help message");
	puts("");
	puts("  * battle - Start battle");
	puts("  * attack [skill] [target] - Attack enemy");
	puts("    a [skill] [target] - ");
	puts("  * attacklist - List skills");
	puts("    al - ");
	puts("  * use [item] - Use Item");
	puts("  * run - Run away from battle");
	puts("");
	puts("  * shop - List buyable items");
	puts("  * buy [name] [amount] - Buy itmes");
	puts("  * sell [name] [amount] - Sell itmes");
	puts("");
	puts("  * inventory - Show inventory");
	puts("    inv - ");
	puts("  * euqip [name] - Equip weapon or armor");
	puts("");
	puts("  * save [name] - Save game");
	puts("  * savelist - List saved games");
	puts("    sl - ");
	puts("  * load [name] - Load game");
	puts("");
	puts("  * quit - save and leave game");
	puts("    exit - ");
}

void battle() {
}
void attack(const Command* cmd) {
	printf("Attacking with skill: %s, target: %s\n", cmd->arg1, cmd->arg2);
	// TODO: 실제 공격 로직 구현
}
void attackList() {
	printf("Listing skills...\n");
	// TODO: 스킬 리스트 출력 로직 구현
}
void useItem(const Command* cmd) {
	printf("Using item: %s\n", cmd->arg1);
	// TODO: 아이템 사용 로직 구현
}
void run() {
	printf("Running away...\n");
	// TODO: 전투 종료 로직 구현
}

void shop() {
	showShop();
}
void buy(const Command* cmd) {
	buyShop(&game.inventory, cmd);
}
void sell(const Command* cmd) {
	sellShop(&game.inventory, cmd);
}

void inventory() {
	showInventory(&game.inventory);
}
void equip(const Command* cmd) {
	printf("Equiping %s...\n", cmd->arg1);
}

void save(const Command* cmd) {
	printf("Saving game as: %s\n", cmd->arg1);
	// TODO: 실제 저장 로직 구현
}
void saveList() {
	printf("Listing saved games...\n");
	// TODO: 실제 저장 목록 로직 구현
}
void load(const Command* cmd) {
	printf("Loading game: %s\n", cmd->arg1);
	// TODO: 실제 로드 로직 구현
}

void quit() {
	printf("Quitting game...\n");
	Command tempCmd = {
		.type = CMD_SAVE,
		.arg1 = "temp",
		.arg2 = "",
		.message = ""
	};
	save(&tempCmd);
	game.state = STATE_FINISHED;
}
