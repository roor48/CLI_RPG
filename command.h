#pragma once

#include "constants.h"

enum COMMAND_TYPE {
	CMD_HELP,
	CMD_ATTACK,
	CMD_ATTACKLIST,
	CMD_USEITEM,
	CMD_RUN,
	CMD_SAVE,
	CMD_LOAD,
	CMD_SAVELIST,
	CMD_QUIT,
	CMD_ERROR,
	CMD_UNKNOWN
};

typedef struct {
	enum COMMAND_TYPE type;
	char arg1[MAX_ARG_LENGTH];
	char arg2[MAX_ARG_LENGTH];
	char message[200];
} Command;

Command parseCommand(const char* query);
