#include "../include/game.h"

#include <stdio.h>
#include <string.h>

#include "../include/input.h"
#include "../include/command.h"
#include "../include/player.h"

void initGame(Game *game);
void executeCommand(Game* game, Command cmd);

void help();
void attack(Game* game, Command cmd);
void attackList(Game* game);
void useItem(Game* game, Command cmd);
void run(Game* game);
void save(Game* game, Command cmd);
void load(Game* game, Command cmd);
void saveList(Game* game);
void quit(Game* game);


unsigned long long startGame() {
	Game game;
	initGame(&game);

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
		executeCommand(&game, cmd);
	}

	return loopCnt;
}

void initGame(Game *game) {
	Player player = (Player){ .health = 100, .level = 1 };
	*game = (Game){ .state = STATE_INIT, .player = player };
}

void executeCommand(Game* game, Command cmd) {
	switch (cmd.type) {
	case CMD_HELP:
		help();
		break;

	case CMD_ATTACK:
		attack(game, cmd);
		break;

	case CMD_ATTACKLIST:
		attackList(game);
		break;

	case CMD_USEITEM:
		useItem(game, cmd);
		break;

	case CMD_RUN:
		run(game);
		break;

	case CMD_SAVE:
		save(game, cmd);
		break;

	case CMD_LOAD:
		load(game, cmd);
		break;

	case CMD_SAVELIST:
		saveList(game);
		break;

	case CMD_QUIT:
		quit(game);
		break;

	case CMD_ERROR:
		printf("%s\n", cmd.message);
		break;

	case CMD_UNKNOWN:
	default:
		printf("Unknown command. Type 'help' for available commands.\n");
		break;
	}
}

void help() {
	puts("Available commands:");
	puts("  help - Show this help message");
	puts("  attack [skill] [target] - Attack enemy");
	puts("  a [skill] [target] - ");
	puts("  attacklist - List skills");
	puts("  al - ");
	puts("  use [item] - Use Item");
	puts("  run - Run away from battle");
	puts("  save [name] - Save game");
	puts("  savelist - List saved games");
	puts("  sl - ");
	puts("  load [name] - Load game");
	puts("  quit - save and leave game");
	puts("  exit - ");
}

void attack(Game *game, Command cmd) {
	printf("Attacking with skill: %s, target: %s\n", cmd.arg1, cmd.arg2);
	// TODO: 실제 공격 로직 구현
}

void attackList(Game *game) {
	printf("Listing skills...\n");
	// TODO: 스킬 리스트 출력 로직 구현
}

void useItem(Game *game, Command cmd) {
	printf("Using item: %s\n", cmd.arg1);
	// TODO: 아이템 사용 로직 구현
}

void run(Game *game) {
	printf("Running away...\n");
	// TODO: 전투 종료 로직 구현
}

void save(Game *game, Command cmd) {
	printf("Saving game as: %s\n", cmd.arg1);
	// TODO: 실제 저장 로직 구현
}


void load(Game *game, Command cmd) {
	printf("Loading game: %s\n", cmd.arg1);
	// TODO: 실제 로드 로직 구현
}

void saveList(Game *game) {
	printf("Listing saved games...\n");
	// TODO: 실제 저장 목록 로직 구현
}

void quit(Game *game) {
	printf("Quitting game...\n");
	save(game, (Command){.arg1 = "temp"});
	game->state = STATE_FINISHED;
}
