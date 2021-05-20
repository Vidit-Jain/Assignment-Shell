#include "commands.h"

#include "../utils/files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
void updateAssignment(String *serverPath, String *assignment)
{
	int flag = folderExists(
		*assignment); // checking if the assignment exists in the given subj

	String *folder;
	folder = makeEmptyString();
	folder = attachString(serverPath->str, "/");
	folder = attachString(
		folder->str,
		assignment->str); // path of the assignment on the server, if exists

	if (!flag) {
		if (!folderExists(*folder)) {
			String *error = makeEmptyString();
			sprintf(
				error->str,
				"\n\tERROR: No such assignment exists for this Subject\n\n");
			printError(*error);
		}
		else {
			// the assignment exists in the server , calling the create function
			String *warning =
				makeString("\n\tNo such assignment exists on your local "
						   "machine, Creating it from the server\n\n");
			printWarning(*warning);
			createAssignment(serverPath, assignment);
		}
	}
	else // the assignment exists in the local machine
	{
		String *get = makeEmptyString();
		sprintf(get->str, "find %s/ -type f -name '*.pdf' > %s/pdfNames.txt",
				folder->str, assignment->str);
		system(get->str);

		chdir(assignment->str);

		FILE *fp = fopen("pdfNames.txt", "r");
		String *dummyString = makeEmptyString();
		size_t stringLength = 0;
		ssize_t readFile;

		int numberOfLines = countLines(*makeString("pdfNames.txt"));

		for (int i = 0; i < numberOfLines; i++) {
			char pdfName[100];
			fscanf(fp, "%s", pdfName);
			String *pdfString = makeString(
				&pdfName[2]); // Deletes all the files before copying over
			char *token;
			token = strtok(pdfString->str, "/");
			char *prev;

			while (token != NULL) {
				prev = token;

				token = strtok(NULL, "/");
			}
			strcpy(pdfString->str, prev);
			deleteFile(*pdfString);
		}
		fclose(fp);

		deleteFile(
			*makeString("pdfNames.txt"));  // Remove temporary file created
		deleteFolder(*makeString("dist")); // Delete the dist folder

		chdir("..");

		String *dist = attachString(folder->str, "/dist");
		String *command = makeEmptyString();

		sprintf(
			command->str, "find %s/ -name '*.pdf' -exec cp -pr '{}' '%s/' ';'",
			folder->str,
			assignment
				->str); // finds all the updated pdf files present in server and
		// copies them to assignment
		system(command->str);

		sprintf(command->str, "cp -r  %s %s > /dev/null", dist->str,
				assignment->str); // copies the updated dist folder from server
								  // into assignment
		system(command->str);
		String *success = makeEmptyString();
		sprintf(success->str, "\n\tAssignment \"%s\" Updated\n\n",
				assignment->str);
		printSuccess(*success);
	}
}

void commandUpdate(tokenMat argsMat)
{
	if (argsMat.numArgs != 1) {
		String *error = makeString(
			"\n\tERROR: Invalid usage of the update command\n\n\tupdate "
			"command syntax: update <assignment> \n\n");
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
		updateAssignment(serverPath, assignmentName);
	}
}