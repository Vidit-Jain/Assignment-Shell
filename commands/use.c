#include "use.h"
void updateUseGlobal()
{
    UseCond = 1;
}
void commandUse(token_mat args_mat)
{
    if (UseCond == 0)
        UseAssignmentName = make_empty_String();
    updateUseGlobal(); //updates global variable to be able to use the USE function

    strcpy(UseAssignmentName->str, args_mat.args[1]); //updates the assignment name variable
    UseAssignmentName->length = strlen(UseAssignmentName->str);
}