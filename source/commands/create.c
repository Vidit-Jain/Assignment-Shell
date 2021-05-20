#include "create.h"
#include "../utils/files.h"
#include "../utils/string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void createAssignment(String *serverPath, String *assignment)
{
	String *folder;

	folder = attachString(serverPath->str, "/");
	folder = attachString(folder->str, assignment->str);

	if (!folderExists(*folder)) {
		String *error = makeString(
			"\n\tERROR: No such assignment exists in server\n\n"); // checks
																   // whether
		printError(*error);										   // assignment
	} // exists on // server/
	else if (folderExists(*assignment)) {
		String *error =
			makeString("\n\tERROR: This assignment already exists\n\n");
		printError(*error); // checks whether
	}						// assignment was
							// already created//
	else {
		createFolder(*assignment); // creates folder for assignment//

		String *dist = attachString(folder->str, "/dist");

		String *command = makeEmptyString();

		sprintf(command->str,
				"find %s/ -name '*.pdf' -exec cp -pr '{}' '%s/' ';'",
				folder->str,
				assignment->str); // finds all pdf files present in server and
								  // copies them to assignment
		system(command->str);
		if (folderExists(*dist)) {
			sprintf(
				command->str, "cp -r  %s %s> /dev/null", dist->str,
				assignment
					->str); // copies dist folder from server into assignment//
			system(command->str);
			String *success = makeEmptyString();
			sprintf(success->str, "\n\tAssignment \"%s\" created\n\n",
					assignment->str);
			printSuccess(*success);
		}
		else {
			String *warning = makeEmptyString();
			sprintf(warning->str,
					"\n\t Assignment \"%s\" created without dist folder\n\n",
					assignment->str);
			printWarning(*warning);
		}
	}
}

void commandCreate(tokenMat argsMat)
{

	if (argsMat.numArgs != 1) {

		String *error = makeString(
			"\n\tERROR: Invalid usage of the create command\n\n\tcreate "
			"command syntax: create <assignment> \n\n");
		printError(*error);
	}
	else if (!isInSubject) {
		String *error =
			makeString("\n\tERROR: You are not in a Subject yet\n\n");
		printError(*error);
	}
	else {
		String *assignmentName = makeString(argsMat.args[1]);
		String *currSubj = getCurrentSubject();
		String *serverPath = makeString("../../Server/");
		serverPath = attachString(serverPath->str, currSubj->str);
		createAssignment(serverPath, assignmentName);
	}
}
