#include "../include/battle.h"

#include "../include/command.h"
#include "../include/enemyManager.h"
#include "../include/player.h"
#include "../include/string_utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Skill parseSkill(const char* skillName);
void printEnemy(const EnemyManager* enemyManager);

void initBattle(Battle* battle) {
    initEnemyManager(&battle->enemyManager);
}

void startBattle(Battle* battle) {
    initBattle(battle);
	spawnEnemy(&battle->enemyManager);
    printEnemy(&battle->enemyManager);
}

int attackBattle(Player *player, Battle *battle, const Command *cmd) {
    Skill skill = parseSkill(cmd->arg1);

	Enemy *enemy = NULL;
    if (isDigitString(cmd->arg2)) {
        // 숫자
		enemy = getEnemyById(&battle->enemyManager, atoi(cmd->arg2));
    }
    else {
        // 문자열
        enemy = getEnemyByName(&battle->enemyManager, cmd->arg2);
    }

    if (skill == SKILL_UNKNOWN || !(player->unlockedSkills[skill])) {
        printf("Unknown skill: %s\n", cmd->arg1);
        return 0;
	}
    if (enemy == NULL) {
        printf("Unknown enemy: %s\n", cmd->arg2);
        return 0;
	}

    // player's attack
    int enemyHealth = attackEnemy(player, skill, enemy);

	if (enemyHealth <= 0) {
        printf("%s is defeated!\n", enemy->name);
		battle->enemyManager.enemyRemain--;
    }
	if (battle->enemyManager.enemyRemain <= 0) {
        printf("All enemies are defeated! You win the battle!\n");

        return 1;
    }

	// enemy's attack
	int playerHealth = allEnemyAttackPlayer(&battle->enemyManager, player);

	if (playerHealth <= 0) {
        printf("You are defeated! Game Over!\n");
        return -1;
    }

    printEnemy(&battle->enemyManager);

    return 0;
}

void printEnemy(const EnemyManager *enemyManager) {
    for (int i = 0; i < enemyManager->enemyIdCounter; i++) {
        if (enemyManager->enemies[i].health <= 0) {
            continue;
        }

        printf("%2d: %s\t%d/%d\n",
            enemyManager->enemies[i].id,
            enemyManager->enemies[i].name, 
            enemyManager->enemies[i].health, 
            enemyManager->enemies[i].maxHealth);
    }
}

Skill parseSkill(const char* skillName) {
    if (strcmp(skillName, "slash") == 0) {
        return SKILL_SLASH;
    }
    else if (strcmp(skillName, "punch") == 0) {
        return SKILL_PUNCH;
    }
    else {
        return SKILL_UNKNOWN;
    }
}
