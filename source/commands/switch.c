#include "switch.h"
#include "../globals.h"
#include "../utils/files.h"
#include "../utils/string.h"
#include "../utils/sysinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_LEN 2000
void exitCurrentDirectory()
{
	String *dots = makeString("..");
	chdir(dots->str);
}

void switchSubject(String subject)
{
	String *homePath;
	homePath = makeEmptyString();

	getcwd(homePath->str, MAX_LEN);
	int strLen = strlen(homePath->str);
	String *currentSubject = getCurrentSubject();
	if (isInSubject) {
		exitCurrentDirectory();
	}
	// going back to the prev dir i.e where all the
	// subj folders are present

	int flag = folderExists(subject); // checking if the subject exists

	if (!flag) {
		String *error = makeEmptyString();
		sprintf(error->str, "\n\tERROR: Subject \"%s\" doesn't exist\n\n",
				subject.str);
		printError(*error);
		if (isInSubject == 1)
			chdir(currentSubject->str);
	}
	else {
		chdir(
			subject.str); // changes the cwd to the subject entered by the user
		isInSubject = 1;
		getcwd(homePath->str, MAX_LEN); // here it gets the path of the cwd i.e
										// after we switch to the subject
	}

	return;
}

void commandSwitch(tokenMat argsMat)
{
	if (argsMat.numArgs != 1) {
		String *error = makeString(
			"\n\tERROR: Invalid usage of the switch command\n\n\tswitch "
			"command syntax: switch <subject>\n\n");
		printError(*error);
	}
	else {
		String *subjectName = makeString(argsMat.args[1]);
		switchSubject(*subjectName);
	}
}
