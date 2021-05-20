#define _GNU_SOURCE
#include "submit.h"
#include "../utils/files.h"
#include "../utils/string.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// supporting function which creates zip for assignment folder
int createAssignmentZip(String path) { return createZip(path, path); }

/* this function is called upon when we are in a subject directory and
the submit command was used properly
without any wrong syntax
*/
void userCommandSubmit(String folder)
{
	String *zip_name = makeEmptyString();

	// Deleting zip if it exists
	sprintf(zip_name->str, "%s.zip", folder.str);
	deleteFile(*zip_name);

	// Creates zip
	int successful = createAssignmentZip(folder);

	if (successful) {
		String *success = makeEmptyString();
		sprintf(success->str, "\n\t%s created successfully\n\n", zip_name->str);
		printSuccess(*success);
	}
	else {
		String *error = makeEmptyString();
		sprintf(error->str, "\n\tERROR: Assignment \"%s\" doesn't exist\n\n",
				folder.str);
		printError(*error);
	}

	ifSubmissionFolder(folder, zip_name);

	if (successful) {
		if (copyToServer(zip_name, folder)) {
			String *success = makeEmptyString();
			sprintf(success->str, "\n\t%s successfully submitted to server\n\n",
					zip_name->str);
			printSuccess(*success);
		}
		else {
			String *error = makeEmptyString();
			sprintf(error->str,
					"\n\tERROR: %s wasn't copied due to duplicate\n\n",
					zip_name->str);
			printError(*error);
		}
	}
}

/* this is the function that is being called by the tokenizer and input is
provided to it and it checks edge cases and then only send the input
further to main submit function which does its operation as defined
*/
void commandSubmit(tokenMat argsMat)
{
	if (argsMat.numArgs != 1) {
		String *error = makeString(
			"\n\tERROR: Invalid usage of the submit command\n\n\tsubmit "
			"command syntax: setup <assignment>\n\n");
		printError(*error);
	}
	else if (!isInSubject) {
		String *error =
			makeString("\n\tERROR: You are not in a Subject yet\n\n");
		printError(*error);
	}
	else {
		String *fileName = makeString(argsMat.args[1]);
		userCommandSubmit(*fileName);
	}
}
