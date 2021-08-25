#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../commands/commands.h"
#include "../utils/files.h"

void tokenizeInput(String Input) {
	tokenMat argsMat;
	argsMat = makeArgsMat();
	char *token;
	token = strtok(Input.str, " "); // tokenize the input string
	int i = 0;

	while (token != NULL) // store the tokenized string in a token matrix
	{
		argsMat.args[i] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
		strcpy(argsMat.args[i], token);
		token = strtok(NULL, " ");
		i++;
	}
	argsMat.numArgs = i - 1; // number of arguments to a command
	argsMat.args[i] = token;
	execute(argsMat); // send it to the required command
}

void execute(tokenMat argsMat) {
	if (strcmp(argsMat.args[0], "switch") == 0) {
		commandSwitch(argsMat);
	} else if (strcmp(argsMat.args[0], "compare") == 0) {
		if (argsMat.numArgs == 1 && useCond == 1) {
			argsMat.args[2] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[2], argsMat.args[1]);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[3] = NULL;
			argsMat.numArgs++;
		}

		commandCompare(argsMat);
	} else if (strcmp(argsMat.args[0], "test") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
		}

		commandTest(argsMat);
	} else if (strcmp(argsMat.args[0], "setup") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
		}

		commandSetup(argsMat);
	} else if (strcmp(argsMat.args[0], "submit") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
		}

		commandSubmit(argsMat);
	} else if (strcmp(argsMat.args[0], "create") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
			// This was intentional
		}

		commandCreate(argsMat);
	} else if (strcmp(argsMat.args[0], "update") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
		}
		commandUpdate(argsMat);
	} else if (strcmp(argsMat.args[0], "tree") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
		}
		commandTree(argsMat);
	} else if (strcmp(argsMat.args[0], "use") == 0) {
		commandUse(argsMat);
	} else if (strcmp(argsMat.args[0], "list") == 0) {
		commandList(argsMat);
	} else if (strcmp(argsMat.args[0], "quit") == 0) {
		exit(0);
	} else {
		String *error = makeEmptyString();
		sprintf(error->str, "\n\tERROR: Invalid command \"%s\"\n\n",
				argsMat.args[0]);
		printError(*error);
	}
}
