#include "../globals.h"
#include "../utils/files.h"
#include "../utils/string.h"
#include "../utils/sysinfo.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_LEN 2000
void exitCurrentDirectory() {
	String *dots = makeString("..");
	chdir(dots->str);
}

void switchSubject(String subject) {
	String *homePath;
	homePath = makeEmptyString();

	getcwd(homePath->str, MAX_LEN);
	String *currentSubject = getCurrentSubject();

	// Going back to the prev dir i.e where all the subj folders are present
	if (isInSubject) {
		exitCurrentDirectory();
	}

	// Checking if the subject exists
	int flag = folderExists(subject);

	if (!flag) {
		String *error = makeEmptyString();
		sprintf(error->str, "\n\tERROR: Subject \"%s\" doesn't exist\n\n",
				subject.str);
		printError(*error);

		if (isInSubject == 1)
			chdir(currentSubject->str);
	} else {
		// Changes the cwd to the subject entered by the user
		chdir(subject.str);
		isInSubject = 1;

		// Gets the path of the cwd after switching into the subject
		getcwd(homePath->str, MAX_LEN);
	}
	return;
}

void commandSwitch(tokenMat argsMat) {
	if (argsMat.numArgs != 1) {
		String *error = makeString(
			"\n\tERROR: Invalid usage of the switch command\n\n\tswitch "
			"command syntax: switch <subject>\n\n");
		printError(*error);
	} else {
		String *subjectName = makeString(argsMat.args[1]);
		switchSubject(*subjectName);
	}
}
