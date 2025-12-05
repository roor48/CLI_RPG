#include "../include/command.h"
#include "../include/constants.h"

#include <stdio.h>
#include <string.h>

void parseHelp(Command *cmd);
void parseStatus(Command* cmd);

void parseBattle(Command* cmd);
void parseEnemyList(Command *cmd);
void parseAttack(Command *cmd);
void parseAttackList(Command *cmd);
void parseUse(Command *cmd);
void parseRun(Command *cmd);

void parseShop(Command *cmd);
void parseBuy(Command *cmd);
void parseSell(Command *cmd);

void parseInventory(Command *cmd);
void parseEquip(Command *cmd);

void parseSave(Command *cmd);
void parseSaveList(Command *cmd);
void parseLoad(Command *cmd);

void parseQuit(Command *cmd);

void parseErrorCommand(Command* cmd);
void parseUnknown(Command* cmd);


char *context, *token;
Command parseCommand(const char* query) {
	Command cmd = { .type = CMD_UNKNOWN, .arg1 = "", .arg2 = "", .message = ""};
	char input[MAX_INPUT_LENGTH + 1];
	strcpy_s(input, sizeof(input), query);

	context = NULL;
	token = strtok_s(input, " ", &context);

	if (token == NULL) {
		return cmd;
	}

	// ¸í·É¾î ÆÄ½Ì
	if (strcmp(token, "help") == 0) {
		parseHelp(&cmd);
	}
	else if (strcmp(token, "status") == 0) {
		parseStatus(&cmd);
	}
	// battle
	else if (strcmp(token, "battle") == 0) {
		parseBattle(&cmd);
	}
	else if (strcmp(token, "enemylist") == 0 || strcmp(token, "el") == 0 || strcmp(token, "enemies") == 0) {
		parseEnemyList(&cmd);
	}
	else if (strcmp(token, "a") == 0 || strcmp(token, "attack") == 0) {
		parseAttack(&cmd);
	}
	else if (strcmp(token, "al") == 0 || strcmp(token, "attacklist") == 0) {
		parseAttackList(&cmd);
	}
	else if (strcmp(token, "use") == 0) {
		parseUse(&cmd);
	}
	else if (strcmp(token, "run") == 0) {
		parseRun(&cmd);
	}
	// shop
	else if (strcmp(token, "shop") == 0) {
		parseShop(&cmd);
	}
	else if (strcmp(token, "buy") == 0) {
		parseBuy(&cmd);
	}
	else if (strcmp(token, "sell") == 0) {
		parseSell(&cmd);
	}
	// inventory
	else if (strcmp(token, "inventory") == 0 || strcmp(token, "inv") == 0) {
		parseInventory(&cmd);
	}
	else if (strcmp(token, "equip") == 0) {
		parseEquip(&cmd);
	}
	// save/load
	else if (strcmp(token, "save") == 0) {
		parseSave(&cmd);
	}
	else if (strcmp(token, "sl") == 0 || strcmp(token, "savelist") == 0) {
		parseSaveList(&cmd);
	}
	else if (strcmp(token, "load") == 0) {
		parseLoad(&cmd);
	}
	// exit
	else if (strcmp(token, "exit") == 0 || strcmp(token, "quit") == 0) {
		parseQuit(&cmd);
	}
	// Error
	else {
		parseUnknown(&cmd);
	}

	return cmd;
}

void parseHelp(Command *cmd) {
	cmd->type = CMD_HELP;
}
void parseStatus(Command* cmd) {
	cmd->type = CMD_STATUS;
}

void parseBattle(Command* cmd) {
	cmd->type = CMD_BATTLE;
}
void parseEnemyList(Command* cmd) {
	cmd->type = CMD_ENEMYLIST;
}
void parseAttack(Command *cmd) {
	cmd->type = CMD_ATTACK;
	// attack [skill] [target]
	token = strtok_s(NULL, " ", &context);
	if (token == NULL) {
		cmd->type = CMD_ERROR;
		strcpy_s(cmd->message, sizeof(cmd->message), "Error: Missing skill name");
		return;
	}
	if (strlen(token) >= MAX_ARG_LENGTH) {
		cmd->type = CMD_ERROR;
		sprintf_s(cmd->message, sizeof(cmd->message), "Error: Skill name too long (max %d characters).", MAX_ARG_LENGTH - 1);
		return;
	}
	strcpy_s(cmd->arg1, sizeof(cmd->arg1), token);
	
	token = strtok_s(NULL, " ", &context);
	if (token == NULL) {
		cmd->type = CMD_ERROR;
		strcpy_s(cmd->message, sizeof(cmd->message), "Error: Missing target name");
		return;
	}
	if (strlen(token) >= MAX_ARG_LENGTH) {
		cmd->type = CMD_ERROR;
		sprintf_s(cmd->message, sizeof(cmd->message), "Error: Target name too long (max %d characters).", MAX_ARG_LENGTH - 1);
		return;
	}
	strcpy_s(cmd->arg2, sizeof(cmd->arg2), token);
}
void parseAttackList(Command *cmd) {
	cmd->type = CMD_ATTACKLIST;
}
void parseUse(Command *cmd) {
	cmd->type = CMD_USECONSUMABLE;
	// use [item]
	token = strtok_s(NULL, " ", &context);
	if (token == NULL) {
		cmd->type = CMD_ERROR;
		strcpy_s(cmd->message, sizeof(cmd->message), "Error: Missing item name");
		return;
	}
	if (strlen(token) >= MAX_ARG_LENGTH) {
		cmd->type = CMD_ERROR;
		sprintf_s(cmd->message, sizeof(cmd->message), "Error: Item name too long (max %d characters).", MAX_ARG_LENGTH - 1);
		return;
	}
	strcpy_s(cmd->arg1, sizeof(cmd->arg1), token);
}
void parseRun(Command *cmd) {
	cmd->type = CMD_RUN;
}

void parseShop(Command *cmd) {
	cmd->type = CMD_SHOP;
}
void parseBuy(Command *cmd) {
	cmd->type = CMD_BUY;
	// buy [item] [amount]
	token = strtok_s(NULL, " ", &context);
	if (token == NULL) {
		cmd->type = CMD_ERROR;
		strcpy_s(cmd->message, sizeof(cmd->message), "Error: Missing item name");
		return;
	}
	if (strlen(token) >= MAX_ARG_LENGTH) {
		cmd->type = CMD_ERROR;
		sprintf_s(cmd->message, sizeof(cmd->message), "Error: item name too long (max %d characters).", MAX_ARG_LENGTH - 1);
		return;
	}
	strcpy_s(cmd->arg1, sizeof(cmd->arg1), token);

	token = strtok_s(NULL, " ", &context);
	if (token == NULL) {
		token = "1"; // default 1
	}
	else if (strlen(token) >= MAX_ARG_LENGTH) {
		cmd->type = CMD_ERROR;
		sprintf_s(cmd->message, sizeof(cmd->message), "Error: item amount too long (max %d characters).", MAX_ARG_LENGTH - 1);
		return;
	}
	strcpy_s(cmd->arg2, sizeof(cmd->arg2), token);
}
void parseSell(Command* cmd) {
	cmd->type = CMD_SELL;
	// sell [item] [amount]
	token = strtok_s(NULL, " ", &context);
	if (token == NULL) {
		cmd->type = CMD_ERROR;
		strcpy_s(cmd->message, sizeof(cmd->message), "Error: Missing item name");
		return;
	}
	if (strlen(token) >= MAX_ARG_LENGTH) {
		cmd->type = CMD_ERROR;
		sprintf_s(cmd->message, sizeof(cmd->message), "Error: item name too long (max %d characters).", MAX_ARG_LENGTH - 1);
		return;
	}
	strcpy_s(cmd->arg1, sizeof(cmd->arg1), token);

	token = strtok_s(NULL, " ", &context);
	if (token == NULL) {
		token = "1"; // default 1
	}
	else if (strlen(token) >= MAX_ARG_LENGTH) {
		cmd->type = CMD_ERROR;
		sprintf_s(cmd->message, sizeof(cmd->message), "Error: item amount too long (max %d characters).", MAX_ARG_LENGTH - 1);
		return;
	}
	strcpy_s(cmd->arg2, sizeof(cmd->arg2), token);
}

void parseInventory(Command *cmd) {
	cmd->type = CMD_INVENTORY;
}
void parseEquip(Command *cmd) {
	cmd->type = CMD_EQUIP;
	// equip [name]
	token = strtok_s(NULL, " ", &context);
	if (token == NULL) {
		cmd->type = CMD_ERROR;
		strcpy_s(cmd->message, sizeof(cmd->message), "Error: Missing weapon or armor name");
		return;
	}
	if (strlen(token) >= MAX_ARG_LENGTH) {
		cmd->type = CMD_ERROR;
		sprintf_s(cmd->message, sizeof(cmd->message), "Error: name too long (max %d characters).", MAX_ARG_LENGTH - 1);
		return;
	}
	strcpy_s(cmd->arg1, sizeof(cmd->arg1), token);
}

void parseSave(Command *cmd) {
	cmd->type = CMD_SAVE;
	// save [name]
	token = strtok_s(NULL, " ", &context);
	if (token == NULL) {
		cmd->type = CMD_ERROR;
		strcpy_s(cmd->message, sizeof(cmd->message), "Error: Missing save name");
		return;
	}
	if (strlen(token) >= MAX_ARG_LENGTH) {
		cmd->type = CMD_ERROR;
		sprintf_s(cmd->message, sizeof(cmd->message), "Error: Save name too long (max %d characters).", MAX_ARG_LENGTH - 1);
		return;
	}
	strcpy_s(cmd->arg1, sizeof(cmd->arg1), token);
}
void parseSaveList(Command *cmd) {
	cmd->type = CMD_SAVELIST;
}
void parseLoad(Command *cmd) {
	cmd->type = CMD_LOAD;
	// load [name]
	token = strtok_s(NULL, " ", &context);
	if (token == NULL) {
		cmd->type = CMD_ERROR;
		strcpy_s(cmd->message, sizeof(cmd->message), "Error: Missing load name");
		return;
	}
	if (strlen(token) >= MAX_ARG_LENGTH) {
		cmd->type = CMD_ERROR;
		sprintf_s(cmd->message, sizeof(cmd->message), "Error: Load name too long (max %d characters).", MAX_ARG_LENGTH - 1);
		return;
	}
	strcpy_s(cmd->arg1, sizeof(cmd->arg1), token);
}

void parseQuit(Command *cmd) {
	cmd->type = CMD_QUIT;
}

void parseErrorCommand(Command *cmd) {
	cmd->type = CMD_ERROR;
}
void parseUnknown(Command *cmd){
	cmd->type = CMD_UNKNOWN;
}
