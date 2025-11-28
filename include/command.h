#pragma once

#include "constants.h"

typedef enum {
	CMD_HELP,
	CMD_ATTACK,
	CMD_ATTACKLIST,
	CMD_INVENTORY,
	CMD_SHOP,
	CMD_BUY,
	CMD_SELL,
	CMD_EQUIP,
	CMD_USEITEM,
	CMD_RUN,
	CMD_SAVE,
	CMD_LOAD,
	CMD_SAVELIST,
	CMD_QUIT,
	CMD_ERROR,
	CMD_UNKNOWN
} COMMAND_TYPE;

typedef struct {
	COMMAND_TYPE type;
	char arg1[MAX_ARG_LENGTH];
	char arg2[MAX_ARG_LENGTH];
	char message[200];
} Command;

Command parseCommand(const char* query);
