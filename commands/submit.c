#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "../utils/string.h"
#include "submit.h"
#include "../utils/files.h"

int createAssignmentZip(String path)
{
    return createZip(path, path);
}

void userCommandSubmit(String folder)
{
    String *zip_name = make_empty_String();

    // Deleting zip if it exists
    sprintf(zip_name->str, "%s.zip", folder.str);
    deleteFile(*zip_name);

    // Creates zip
    int successful = createAssignmentZip(folder);

    if (successful)
        printf("%s created successfully\n", zip_name->str);
    else
        printf("Assignment \"%s\" doesn't exist\n", folder.str);

    if (successful)
    {
        if (copy_to_server(find_zip(zip_name)))
        {
            printf("%s successfully submitted to server\n\n", zip_name->str);
        }
        else
        {
            printf("%s caused error in copying\n\n", zip_name->str);
        }
    }
}

void commandSubmit(token_mat args_mat)
{
    if (args_mat.num_args != 1)
    {
        printf("\n\tInvalid usage of the submit command\n\n");
        printf("\tsubmit command syntax: submit <assignment> \n\n");
    }
    else if (!isInSubject)
    {
        printf("\n\tError: You are not in a Subject yet\n\n");
    }
    else
    {
        String *fileName = make_String(args_mat.args[1]);
        userCommandSubmit(*fileName);
    }
}