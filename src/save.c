#include "../include/save.h"

#include "../lib/cJSON.h"
#include "../include/player.h"
#include "../include/inventory.h"
#include "../include/constants.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>

#define SAVE_DIR "saves/"

/*
 * @brief 디렉토리 존재 확인 및 생성
 * 
 * @return 성공 시 1, 실패 시 0
 */
int checkAndCreateDirectory(const char *path) {
	// '_'없으면 에러
	if (_access(path, 0) == -1) {  // 0 = 존재 확인
		// 디렉토리가 없으면 생성
		if (_mkdir(path) != 0) {
			printf("Error: Failed to create directory: %s\n", path);
			return 0;
		}
		printf("Created directory: %s\n", path);
	}
	
	return 1;
}

cJSON* playerToJSON(const Player* player) {
	cJSON* json = cJSON_CreateObject();
	
	cJSON_AddNumberToObject(json, "maxHealth", player->maxHealth);
	cJSON_AddNumberToObject(json, "health", player->health);
	cJSON_AddNumberToObject(json, "level", player->level);
	cJSON_AddNumberToObject(json, "maxExperience", player->maxExperience);
	cJSON_AddNumberToObject(json, "experience", player->experience);
	
	// 스킬 배열
	cJSON* skills = cJSON_CreateArray();
	for (int i = 0; i < MAX_SKILL_TYPES; i++) {
		cJSON_AddItemToArray(skills, cJSON_CreateNumber(player->unlockedSkills[i]));
	}
	cJSON_AddItemToObject(json, "unlockedSkills", skills);
	
	cJSON_AddNumberToObject(json, "currentWeapon", player->currentWeapon);
	cJSON_AddNumberToObject(json, "currentArmor", player->currentArmor);
	
	return json;
}

void jsonToPlayer(const cJSON* json, Player* player) {
	player->maxHealth = cJSON_GetObjectItem(json, "maxHealth")->valueint;
	player->health = cJSON_GetObjectItem(json, "health")->valueint;
	player->level = cJSON_GetObjectItem(json, "level")->valueint;
	player->maxExperience = cJSON_GetObjectItem(json, "maxExperience")->valueint;
	player->experience = cJSON_GetObjectItem(json, "experience")->valueint;
	
	// 스킬 배열
	cJSON* skills = cJSON_GetObjectItem(json, "unlockedSkills");
	int i = 0;
	cJSON* skill = NULL;
	cJSON_ArrayForEach(skill, skills) {
		if (i < MAX_SKILL_TYPES) {
			player->unlockedSkills[i++] = skill->valueint;
		}
	}
	
	player->currentWeapon = cJSON_GetObjectItem(json, "currentWeapon")->valueint;
	player->currentArmor = cJSON_GetObjectItem(json, "currentArmor")->valueint;
}

cJSON* inventoryToJSON(const Inventory* inventory) {
	cJSON* json = cJSON_CreateObject();
	
	cJSON_AddNumberToObject(json, "gold", inventory->gold);
	
	// 소모템 배열
	cJSON* consumables = cJSON_CreateArray();
	for (int i = 0; i < MAX_CONSUMABLE_TYPES; i++) {
		cJSON_AddItemToArray(consumables, cJSON_CreateNumber(inventory->consumables[i]));
	}
	cJSON_AddItemToObject(json, "consumables", consumables);
	
	// 무기 배열
	cJSON* weapons = cJSON_CreateArray();
	for (int i = 0; i < MAX_WEAPON_TYPES; i++) {
		cJSON_AddItemToArray(weapons, cJSON_CreateNumber(inventory->weapons[i]));
	}
	cJSON_AddItemToObject(json, "weapons", weapons);
	
	// 방어구 배열
	cJSON* armors = cJSON_CreateArray();
	for (int i = 0; i < MAX_ARMOR_TYPES; i++) {
		cJSON_AddItemToArray(armors, cJSON_CreateNumber(inventory->armors[i]));
	}
	cJSON_AddItemToObject(json, "armors", armors);
	
	return json;
}

void jsonToInventory(const cJSON* json, Inventory* inventory) {
	inventory->gold = cJSON_GetObjectItem(json, "gold")->valueint;
	
	// 소모템 배열
	cJSON* consumables = cJSON_GetObjectItem(json, "consumables");
	int i = 0;
	cJSON* consumable = NULL;
	cJSON_ArrayForEach(consumable, consumables) {
		if (i < MAX_CONSUMABLE_TYPES) {
			inventory->consumables[i++] = consumable->valueint;
		}
	}
	
	// 무기 배열
	cJSON* weapons = cJSON_GetObjectItem(json, "weapons");
	i = 0;
	cJSON* weapon = NULL;
	cJSON_ArrayForEach(weapon, weapons) {
		if (i < MAX_WEAPON_TYPES) {
			inventory->weapons[i++] = weapon->valueint;
		}
	}
	
	// 방어구 배열
	cJSON* armors = cJSON_GetObjectItem(json, "armors");
	i = 0;
	cJSON* armor = NULL;
	cJSON_ArrayForEach(armor, armors) {
		if (i < MAX_ARMOR_TYPES) {
			inventory->armors[i++] = armor->valueint;
		}
	}
}

int saveGame(const Player* player, const Inventory* inventory, const char* filename) {
	if (player == NULL || inventory == NULL) {
		printf("Error: player or inventory is NULL.\n");
		return 0;
	}
	
	// 저장 디렉토리 확인 및 생성
	if (!checkAndCreateDirectory(SAVE_DIR)) {
		return 0;
	}
	
	// JSON 객체 생성
	cJSON* root = cJSON_CreateObject();
	
	// Player와 Inventory를 JSON으로 변환
	cJSON_AddItemToObject(root, "player", playerToJSON(player));
	cJSON_AddItemToObject(root, "inventory", inventoryToJSON(inventory));
	
	// JSON 문자열로 변환 (포맷팅)
	char* jsonString = cJSON_Print(root);
	
	// 파일 경로 생성
	char filepath[256];
	sprintf_s(filepath, sizeof(filepath), "%s%s.json", SAVE_DIR, filename);
	
	// 파일에 저장
	FILE* file = NULL;
	errno_t err = fopen_s(&file, filepath, "w");
	if (err != 0 || file == NULL) {
		printf("Error: Failed to open file: %s\n", filepath);
		cJSON_Delete(root);
		free(jsonString);
		return 0;
	}
	
	fprintf(file, "%s", jsonString);
	fclose(file);
	
	// 메모리 해제
	cJSON_Delete(root);
	free(jsonString);
	
	return 1;
}

int loadGame(Player* player, Inventory* inventory, const char* filename) {
	if (!player || !inventory) {
		printf("Error: player or inventory is NULL.\n");
		return 0;
	}
	
	// 파일 경로 생성
	char filepath[256];
	sprintf_s(filepath, sizeof(filepath), "%s%s.json", SAVE_DIR, filename);
	
	// 바이너리로 파일 열기
	FILE* file = NULL;
	errno_t err = fopen_s(&file, filepath, "rb");
	if (err != 0 || !file) {
		printf("Error: Failed to open file: %s\n", filepath);
		return 0;
	}
	
	// 파일 크기 확인
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	// 파일 크기 유효성 검사
	if (fileSize <= 0 || fileSize > 1024 * 1024 * 10) {  // 최대 10MB
		printf("Error: File size too big or low: %ld\n", fileSize);
		fclose(file);
		return 0;
	}
	
	// 파일 내용 읽기
	char* jsonString = (char*)malloc(fileSize + 1);
	if (jsonString == NULL) {
		printf("Error: Failed to alloc.\n");
		fclose(file);
		return 0;
	}
	
	size_t bytesRead = fread(jsonString, sizeof(char), fileSize, file);
	if (bytesRead != (size_t)fileSize) {
		printf("Error: Failed to read file. fileSize: %ld, read: %zu\n", fileSize, bytesRead);
		free(jsonString);
		fclose(file);
		return 0;
	}
	
	jsonString[bytesRead] = '\0';
	fclose(file);
	
	// JSON 파싱
	cJSON* root = cJSON_Parse(jsonString);
	free(jsonString);
	
	if (!root) {
		printf("Error: Failed to parse JSON.\n");
		return 0;
	}
	
	// Player와 Inventory 복원
	cJSON* playerJSON = cJSON_GetObjectItem(root, "player");
	cJSON* inventoryJSON = cJSON_GetObjectItem(root, "inventory");
	
	if (playerJSON) {
		jsonToPlayer(playerJSON, player);
	}
	
	if (inventoryJSON) {
		jsonToInventory(inventoryJSON, inventory);
	}
	
	cJSON_Delete(root);
	return 1;
}

void listSavedGames() {
	
	// "saves/*.json"
	char searchPattern[256];
	sprintf_s(searchPattern, sizeof(searchPattern), "%s*.json", SAVE_DIR);
	
	// "saves/*.json"와 일치하는 파일 찾기
	struct _finddata_t fileData;
	intptr_t handle = _findfirst(searchPattern, &fileData);
	
	if (handle == -1) {
		printf("No saved games found.\n");
		return;
	}
	printf("Saved games:\n");
	
	do {
		char filename[256];
		strcpy_s(filename, sizeof(filename), fileData.name);

		size_t len = strlen(filename);
		filename[len - 5] = '\0';  // .json 제거
		
		printf("  %s\n", filename);
	} while (_findnext(handle, &fileData) == 0);
	
	_findclose(handle);
}
