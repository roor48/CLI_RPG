#include "../include/game.h"

#include <stdio.h>
#include <string.h>

#include "../include/input.h"
#include "../include/command.h"
#include "../include/player.h"
#include "../include/inventory.h"
#include "../include/shop.h"
#include "../include/battle.h"

void initGame();
void executeCommand(const Command* cmd);

void help();
void battle();
void enemyList();
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


Game game = {0};
unsigned long long startGame() {
	initGame();

	char query[MAX_INPUT_LENGTH];

	game.state = STATE_RUNNING;
	game.scene = SCENE_MAIN;
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
	game.state = STATE_INIT;
	game.scene = SCENE_UNKNOWN;

	game.player.maxHealth = 100;
	game.player.health = 100;
	game.player.level = 1;
	game.player.unlockedSkills[SKILL_PUNCH] = 1;
	
	game.inventory.gold = 10000;
	
	initBattle(&game.battle);

	initShop();
}

void executeCommand(const Command* cmd) {
	if (cmd->type == CMD_HELP) {
		help();
		return;
	}

	if (game.scene == SCENE_BATTLE) {
		// ���� �������� ���� ���� ���ɾ ���
		switch (cmd->type) {
			case CMD_ENEMYLIST:
				enemyList();
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
			case CMD_UNKNOWN:
				printf("Unknown command. Type 'help' for available commands.\n");
				break;
			default:
				printf("You can use only battle commands\n");
				break;
		}

		return;
	}
	switch (cmd->type) {
			// battle
		case CMD_BATTLE:
			battle();
			break;

		case CMD_ATTACKLIST:
			attackList();
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
			printf("Unknown command. Type 'help' for available commands.\n");
			break;
		
		default:
			printf("You can use only main commands\n");
			break;
	}
}

void help() {
	puts("Available commands:");
	puts("Main commands:");
		puts("  * help - Show this help message");
		puts("  * battle - Start battle");

		puts("");
		puts("  shop commands:");
			puts("    * shop - List buyable items");
			puts("    * buy [name] [amount] - Buy itmes");
			puts("    * sell [name] [amount] - Sell itmes");

		puts("");
		puts("  inventory commands:");
			puts("    * inventory - Show inventory");
			puts("      inv - ");
			puts("    * euqip [name] - Equip weapon or armor");

		puts("");
		puts("  save comands:");
			puts("    * save [name] - Save game");
			puts("    * savelist - List saved games");
			puts("      sl - ");
			puts("    * load [name] - Load game");

		puts("");
		puts("  quit commands:");
		puts("    * quit - save and leave game");
		puts("      exit - ");

	puts("");
	puts("Battle commmands:");
		puts("  * attack [skill] [target] - Attack enemy");
		puts("    a [skill] [target] - ");
		puts("  * attacklist - List skills");
		puts("    al - ");
		puts("  * use [item] - Use Item");
		puts("  * run - Run away from battle");

}

void battle() {
	game.scene = SCENE_BATTLE;
	game.player.health = game.player.maxHealth;
	startBattle(&game.battle);
}
void enemyList() {
	printEnemy(&game.battle.enemyManager);
}
void attack(const Command* cmd) {
	printf("Attacking with skill: %s, target: %s\n", cmd->arg1, cmd->arg2);
	int status = attackBattle(&game.player, &game.battle, cmd);

	if (status == 1) {
		// �¸�
		printf("You won the battle!\n");
		// ���� ����
		game.scene = SCENE_MAIN;
	}
	else if (status == -1) {
		// �й�
		printf("You lost the battle!\n");
		// ���� ����
		game.scene = SCENE_MAIN;
	}
}
void attackList() {
	printf("Listing skills...\n");
	// TODO: ��ų ����Ʈ ��� ���� ����
}
void useItem(const Command* cmd) {
	printf("Using item: %s\n", cmd->arg1);
	// TODO: ������ ��� ���� ����
}
void run() {
	printf("You ran away from the battle!\n");
	game.scene = SCENE_MAIN;
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
	// TODO: ���� ���� ���� ����
}
void saveList() {
	printf("Listing saved games...\n");
	// TODO: ���� ���� ��� ���� ����
}
void load(const Command* cmd) {
	printf("Loading game: %s\n", cmd->arg1);
	// TODO: ���� �ε� ���� ����
}

void quit() {
	printf("Quitting game...\n");
	Command tempCmd = {
		.type = CMD_SAVE,
		.arg1 = "auto",
		.arg2 = "",
		.message = ""
	};
	save(&tempCmd);
	game.state = STATE_FINISHED;
}
