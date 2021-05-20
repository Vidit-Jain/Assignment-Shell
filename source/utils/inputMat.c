#include "inputMat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

tokenMat makeArgsMat() // initializes the token matrix to store user command
					   // name and arguments
{
	tokenMat argsMat;

	argsMat.args = malloc(sizeof(char *) * MAX_NUM_OF_TOKENS);
	for (int i = 0; i < MAX_NUM_OF_TOKENS; i++) {
		argsMat.args[i] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
	}
	return argsMat;
}