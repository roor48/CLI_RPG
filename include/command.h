#pragma once

#include "constants.h"

/*
 * @brief 명령어 타입
 */
typedef enum COMMAND_TYPE {
	CMD_HELP,
	CMD_STATUS,

	CMD_BATTLE,
	CMD_ENEMYLIST,
	CMD_ATTACK,
	CMD_ATTACKLIST,
	CMD_USECONSUMABLE,
	CMD_RUN,

	CMD_SHOP,
	CMD_BUY,
	CMD_SELL,

	CMD_INVENTORY,
	CMD_EQUIP,

	CMD_SAVE,
	CMD_SAVELIST,
	CMD_LOAD,
	
	CMD_RESET,

	CMD_QUIT,

	CMD_ERROR,
	CMD_UNKNOWN

} COMMAND_TYPE;

/*
 * @brief 명령어 구조체
 */
typedef struct Command {
	COMMAND_TYPE type;
	char arg1[MAX_ARG_LENGTH + 1];
	char arg2[MAX_ARG_LENGTH + 1];
	char message[200];
} Command;

/*
 * @brief 명령어 파싱
 *
 * @param *query 입력된 명령어 문자열
 *
 * @return 명령어 구조체
 */
Command parseCommand(const char* query);
