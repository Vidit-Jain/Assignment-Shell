#include "prompt.h"
#include "../globals.h"
#include "../utils/files.h"
#include "../utils/string.h"
#include "../utils/sysinfo.h"

#include <unistd.h>

void initialize() // initialize the home_path and prev_path
{
	homePath.str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
	getcwd(homePath.str, MAX_TOKEN_LENGTH);
	homePath.length = strlen(homePath.str);

	prevPath.str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
	getcwd(prevPath.str, MAX_TOKEN_LENGTH);
	prevPath.length = strlen(prevPath.str);
}

void promptPrint() // print the username and subject to give terminal feel
{
	if (useCond) {
		printf(BLUE);
		printf("<%s:", getUsername().str);
		printf(RESET);
		printf(ORANGE);
		printf("%s", getCurrentSubject()->str);
		printf(RESET);
		printf(BLUE);
		printf("/");
		printf(RESET);
		printf(LIGHT_PURPLE);
		printf("<%s>", useAssignmentName->str);
		printf(RESET);
		printf(BLUE);
		printf("$ ");
		printf(RESET);
	} else {
		printf(BLUE);
		printf("<%s:", getUsername().str);
		printf(RESET);
		printf(ORANGE);
		printf("%s", getCurrentSubject()->str);
		printf(RESET);
		printf(BLUE);
		printf("/$ ");
		printf(RESET);
	}

	fflush(stdout);
}
