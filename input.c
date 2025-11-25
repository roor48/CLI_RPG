#include "input.h"
#include "constants.h"

#include <stdio.h>

size_t getInput(char *query) {
	printf("> ");

	if (fgets(query, sizeof(char) * (MAX_INPUT_LENGTH-1), stdin) == NULL) {
		printf("\nInput error occurred.\n");
		return 0;
	}

	size_t len = strlen(query);
	if (len > 0 && query[len - 1] == '\n') {
		query[len - 1] = '\0';
	}
	else {
		printf("Error: Input too long (max %d characters). Please try again.\n", MAX_INPUT_LENGTH - 1);
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		return 0;
	}
	
	return len-1;
}
