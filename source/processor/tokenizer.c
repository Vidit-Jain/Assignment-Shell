#include "tokenizer.h"
#include "../commands/compare.h"
#include "../commands/create.h"
#include "../commands/execvp.h"
#include "../commands/setup.h"
#include "../commands/submit.h"
#include "../commands/switch.h"
#include "../commands/test.h"
#include "../commands/tree.h"
#include "../commands/update.h"
#include "../commands/use.h"
void tokenizeInput(String Input)
{
	tokenMat args_mat;
	args_mat = makeArgsMat();
	char *token;
	token = strtok(Input.str, " "); // tokenize the input string
	int i = 0;

	if (strcmp(token, "list") == 0) // rename list to ls
	{
		strcpy(token, "ls");
	}
	if (strcmp(token, "quit") == 0) {
		exit(0);
	}
	while (token != NULL) // store the tokenized string in a token matrix
	{
		args_mat.args[i] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
		strcpy(args_mat.args[i], token);
		token = strtok(NULL, " ");
		i++;
	}
	args_mat.numArgs = i - 1; // number of arguments to a command
	args_mat.args[i] = token;
	execute(args_mat); // send it to the required command
}

void execute(tokenMat argsMat)
{
	if (strcmp(argsMat.args[0], "switch") == 0) {
		commandSwitch(argsMat);
	}
	else if (strcmp(argsMat.args[0], "compare") == 0) {
		if (argsMat.numArgs == 1 && useCond == 1) {
			argsMat.args[2] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[2], argsMat.args[1]);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[3] = NULL;
			argsMat.numArgs++;
		}

		commandCompare(argsMat);
	}
	else if (strcmp(argsMat.args[0], "test") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
		}

		commandTest(argsMat);
	}
	else if (strcmp(argsMat.args[0], "setup") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
		}

		commandSetup(argsMat);
	}
	else if (strcmp(argsMat.args[0], "submit") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
		}

		commandSubmit(argsMat);
	}
	else if (strcmp(argsMat.args[0], "create") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
			// This was intentional
		}

		commandCreate(argsMat);
	}
	else if (strcmp(argsMat.args[0], "update") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
		}
		commandUpdate(argsMat);
	}
	else if (strcmp(argsMat.args[0], "tree") == 0) {
		if (argsMat.numArgs == 0 && useCond == 1) {
			argsMat.args[1] = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
			strcpy(argsMat.args[1], useAssignmentName->str);
			argsMat.args[2] = NULL;
			argsMat.numArgs++;
		}
		commandTree(argsMat);
	}
	else if (strcmp(argsMat.args[0], "use") == 0) {
		commandUse(argsMat);
	}
	else if (strcmp(argsMat.args[0], "ls") == 0) {
		printf("\n");
		exec(argsMat);
		printf("\n");
	}
	else {
		String *error = makeEmptyString();
		sprintf(error->str, "\n\tERROR: Invalid command \"%s\"\n\n",
				argsMat.args[0]);
		printError(*error);
	}
}
