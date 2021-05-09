#include "use.h"
#include "../utils/files.h"

void updateUseGlobal()
{
    UseCond = 1;
}

void useAssignment(String assignmentName) {
    if (!folderExists(assignmentName)) {
        printf("\n\tAssignment \"%s\" doesn't exist\n\n", assignmentName.str);
        return;
    }

    // Assigns the assignment name to the global variable
    UseAssignmentName = make_String(assignmentName.str);
    UseAssignmentName->length = strlen(UseAssignmentName->str);

    updateUseGlobal(); //updates global variable to be able to use the USE function
}

void commandUse(token_mat args_mat)
{
    if (args_mat.num_args != 1) {
        printf("\n\tInvalid usage of the use command\n\n");
        printf("\tuse command syntax: use <assignment>\n\n");
    }
    else if (!isInSubject) {
        printf("\n\tError: You are not in a Subject yet\n\n");
    }
    else {
        String* assignmentName = make_String(args_mat.args[1]);
        useAssignment(*assignmentName);
    }
}