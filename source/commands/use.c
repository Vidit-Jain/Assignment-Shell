#include "use.h"
#include "../utils/files.h"

void updateUseGlobal() { useCond = 1; }

void useAssignment(String assignmentName)
{
	if (!folderExists(assignmentName)) {
		String *error = makeEmptyString();
		sprintf(error->str, "\n\tERROR: Assignment \"%s\" doesn't exist\n\n",
				assignmentName.str);
		printError(*error);
		return;
	}

	// Assigns the assignment name to the global variable
	useAssignmentName = makeString(assignmentName.str);
	useAssignmentName->length = strlen(useAssignmentName->str);

	updateUseGlobal(); // updates global variable to be able to use the USE
					   // function
}

void commandUse(tokenMat argsMat)
{
	if (argsMat.numArgs != 1) {
		String *error =
			makeString("\n\tERROR: Invalid usage of the use command\n\n\tuse "
					   "command syntax: use <assignment> \n\n");
		printError(*error);
	}
	else if (!isInSubject) {
		String *error =
			makeString("\n\tERROR: You are not in a Subject yet\n\n");
		printError(*error);
	}
	else {
		String *assignmentName = makeString(argsMat.args[1]);
		useAssignment(*assignmentName);
	}
}