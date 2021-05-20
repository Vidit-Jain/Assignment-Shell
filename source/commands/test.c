#include "commands.h"
#include "../utils/files.h"
#include "../utils/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void test(String folder)
{
	String *file;

	file = attachString(folder.str, "/dist/submitter.py");

	int flag1 = folderExists(folder) && fileExists(*file);

	if (!flag1) {

		if (!folderExists(folder)) { // checks whether given assignment exists//
			String *error = makeEmptyString();
			sprintf(error->str, "\n\tERROR: Assignment \"%s\" doesn't exist\n",
					folder.str);
			printError(*error);
		}
		else if (!fileExists(*file)) { // checks whether submitter.py exists in
									   // assignment//
			String *error = makeEmptyString();
			sprintf(error->str,
					"\n\tERROR: Assignment \"%s\" cannot be tested as it does "
					"not contain "
					"submitter.py file\n",
					folder.str);
			printError(*error);
		}

		printf("\n");
	}
	else {
		int i = 1;

		String *filename = makeEmptyString();
		String *logfile;

		createFolder(
			*makeString("Logs")); // Creates folder Logs if it doesn't exist

		while (1) {
			sprintf(filename->str, "Logs/%d.txt", i);

			logfile = makeString(filename->str);

			// if such a file doesn't exist we can use it
			if (!fileExists(*logfile))
				break;

			i++;
		}

		printf("\n\t%s will be created\n\n", logfile->str);
		String *runcommand = makeEmptyString();
		sprintf(runcommand->str, "python3 %s/dist/submitter.py > Logs/%d.txt",
				folder.str,
				i); // runs submitter.py and store logs in Logs/i.log file //

		system(runcommand->str);
	}
}

void commandTest(tokenMat argsMat)
{
	if (argsMat.numArgs != 1) {
		String *error =
			makeString("\n\tERROR: Invalid usage of the test command\n\n\ttest "
					   "command syntax: test <assignment>\n\n");
		printError(*error);
	}
	else if (!isInSubject) {
		String *error =
			makeString("\n\tERROR: You are not in a Subject yet\n\n");
		printError(*error);
	}
	else {
		String *assignmentName = makeString(argsMat.args[1]);
		test(*assignmentName);
	}
}
