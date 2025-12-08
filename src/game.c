#include "../include/game.h"

#include <stdio.h>
#include <string.h>

#include "../include/input.h"
#include "../include/command.h"
#include "../include/player.h"
#include "../include/inventory.h"
#include "../include/shop.h"
#include "../include/battle.h"
#include "../include/reward.h"
#include "../include/save.h"

void initGame();
void executeCommand(const Command* cmd);

#pragma region Command Handlers
void help();
void status();

void battle();
void enemyList();
void attack(const Command* cmd);
void attackList();
void use(const Command* cmd);
void run();

void shop();
void buy(const Command* cmd);
void sell(const Command* cmd);

void inventory();
void equip(const Command* cmd);

void save(const Command* cmd);
void saveList();
void load(const Command* cmd);

void reset();

void quit();
#pragma endregion

void unlockSkillLogic();

Game game = {0};
unsigned long long startGame() {
	initGame();

	// 입력 + '\n' + '\0' 때문에 + 2
	char query[MAX_INPUT_LENGTH + 2];

	game.state = STATE_RUNNING;
	game.scene = SCENE_MAIN;
	printf("Game started! Type 'help' for commands.\n");

	if (loadGame(&game.player, &game.inventory, "auto")) {
		printf("Loaded data in auto.\n");
	}
	unsigned long long loopCnt = 0;
	while (game.state != STATE_FINISHED) {
		loopCnt++;

		size_t len = getInput(query);

		if (len == 0) {
			continue;
		}

		Command cmd = parseCommand(query);
		executeCommand(&cmd);

		unlockSkillLogic();
	}

	return loopCnt;
}

void initGame() {
	game.state = STATE_INIT;
	game.scene = SCENE_UNKNOWN;

	game.player = (Player){0};
	game.player.maxHealth = 100;
	game.player.health = 100;
	game.player.level = 1;
	game.player.maxExperience = game.player.level * 10;
	game.player.experience = 0;
	game.player.unlockedSkills[SKILL_PUNCH] = 1;
	game.player.currentWeapon = WEAPON_STICK;
	game.player.currentArmor = ARMOR_CLOTH;

	game.inventory = (Inventory){0};
	game.inventory.gold = 10000;
	game.inventory.weapons[WEAPON_STICK] = 1;
	game.inventory.armors[ARMOR_CLOTH] = 1;
	
	initBattle(&game.battle);
}

void executeCommand(const Command* cmd) {
	if (cmd->type == CMD_UNKNOWN) {
		printf("Unknown command. Type 'help' for available commands.\n");
		return;
	}
	if (cmd->type == CMD_ERROR) {
		printf("%s\n", cmd->message);
		return;
	}

	// 전역적으로 사용 가능한 명령어
	if (cmd->type == CMD_HELP) {
		help();
		return;
	}

	// 배틀에서 사용 가능한 명령어
	if (game.scene == SCENE_BATTLE) {
		// 배틀 전용 명령어
		switch (cmd->type) {
			case CMD_STATUS:
				status();
				break;
			case CMD_ENEMYLIST:
				enemyList();
				break;
			case CMD_ATTACK:
				attack(cmd);
				break;
			case CMD_ATTACKLIST:
				attackList();
				break;
			case CMD_USECONSUMABLE:
				use(cmd);
				break;
			case CMD_RUN:
				run();
				break;

			case CMD_INVENTORY:
				inventory();
				break;

			case CMD_QUIT:
				printf("You cannot quit during battle! Use 'run' first\n");
				break;

			default:
				printf("You can use only battle commands\n");
				break;
		}

		return;
	}

	// 메인에서 사용 가능한 명령어
	if (game.scene == SCENE_MAIN) {
		switch (cmd->type) {
			case CMD_STATUS:
				status();
				break;

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

			// reset
			case CMD_RESET:
				reset();
				break;

			default:
				printf("You can use only main commands\n");
				break;
		}
	}
}

#pragma region Command Handlers
void help() {
	puts("Available commands:");
	puts("Static commands:");
		puts("  * help - Show this help message");
		puts("  * status - Print player status");

	puts("");
	puts("Main commands:");
		puts("  * battle - Start battle");
		puts("  * reset - Reset game datas");

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
			puts("    * quit - Save and leave game");
			puts("      exit - ");

	puts("");
	puts("Battle commmands:");
		puts("  * attack [skill] [target] - Attack enemy");
		puts("    a [skill] [target] - ");
		puts("  * attacklist - List skills");
		puts("    al - ");
		puts("  * use [item] - Use Item");
		puts("  * enemylist - List enemy status");
		puts("    el");
		puts("  * run - Run away from battle");

}
void status() {
	printPlayerStatus(&game.player);
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
		printf("You won the battle!\n");
		game.scene = SCENE_MAIN;

		giveWinReward(&game.inventory, &game.player);
		game.player.health = game.player.maxHealth;
	}
	else if (status == -1) {
		printf("You lost the battle!\n");
		game.scene = SCENE_MAIN;

		giveLoseReward(&game.inventory, &game.player);
		game.player.health = game.player.maxHealth;
	}
}
void attackList() {
	printPlayerSkills(&game.player);
}
void use(const Command* cmd) {
	useConsumable(&game.player, &game.inventory, cmd);
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
	sellShop(&game.inventory, &game.player, cmd);
}

void inventory() {
	showInventory(&game.inventory);
}
void equip(const Command* cmd) {
	equipItem(&game.player, &game.inventory, cmd);
}

void save(const Command* cmd) {
	printf("Saving game as: %s\n", cmd->arg1);
	int success = saveGame(&game.player, &game.inventory, cmd->arg1);

	if (success) {
		printf("Successed to save: %s\n", cmd->arg1);
	}
	else {
		printf("Failed to save: %s\n", cmd->arg1);
	}
}
void saveList() {
	listSavedGames();
}
void load(const Command* cmd) {
	printf("Loading game: %s\n", cmd->arg1);
	loadGame(&game.player, &game.inventory, cmd->arg1);
}

void reset() {
	initGame();
	game.state = STATE_RUNNING;
	game.scene = SCENE_MAIN;
	printf("Game reseted.\n");
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
#pragma endregion

void unlockSkillLogic() {
	if (game.player.level >= 5) {
		if (!hasSkill(&game.player, SKILL_SLASH)) {
			getSkill(&game.player, SKILL_SLASH);
		}
	}
}
