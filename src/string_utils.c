#include "../include/string_utils.h"

#include <ctype.h>
#include <stdlib.h>

void formatNumberWithCommas(char* str, size_t bufSize, int num);

void toLowerCase(char* str) {
	for (int i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);
	}
}

int isDigitString(char* str) {
	for (int i = 0; str[i]; i++) {
		if (isdigit(str[i]) == 0) {
			return 0;
		}
	}
	return 1;
}

void formatNumberWithCommas(char* str, size_t strSize, int num) {
	if (strSize < INT_FORMAT_SIZE) return;

	// 0 처리
	if (num == 0) {
		str[0] = '0';
		str[1] = '\0';
		return;
	}
	
	// 음수 처리
	int isNegative = 0;
	if (num < 0) {
		isNegative = 1;
		num = -num;
	}
	
	// 임시 버퍼에 역순으로 저장
	char temp[INT_FORMAT_SIZE];
	int idx = 0;
	int divCnt = 0;
	
	temp[idx++] = '\0';
	while (num > 0) {
		temp[idx++] = (num % 10) + '0';
		num /= 10;
		divCnt++;
		if (divCnt % 3 == 0 && num > 0) {
			temp[idx++] = ',';
		}
	}

	// 음수 부호 추가
	if (isNegative) {
		temp[idx++] = '-';
	}

	// 뒤집어서 str에 복사
	int writeIdx = 0;
	for (int i = idx - 1; i >= 0 && writeIdx < strSize - 1; i--) {
		str[writeIdx++] = temp[i];
	}
}

char* formatNum(int num) {
	static char buffers[4][INT_FORMAT_SIZE];
	static int index = 0;
	
	index = (index + 1) % 4;
	formatNumberWithCommas(buffers[index], sizeof(buffers[index]), num);
	return buffers[index];
}
