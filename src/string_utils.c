#include "../include/string_utils.h"

#include <ctype.h>

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
