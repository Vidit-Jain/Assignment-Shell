#include "update.h"



void updateAssignment(String *serverPath,String *assignment)
{
    int flag = folderExists(*assignment);//checking if the assignment exists in the given subj

    String *folder;
    folder = make_empty_String();
    folder = attach_String(serverPath->str, "/");
    folder = attach_String(folder->str, assignment->str);//path of the assignment on the server, if exists

    if(!flag)
    {
        if (!folderExists(*folder))
            printf("\n\tERROR! No such assignment exists for this Subject\n\n");
        else
        {
            //the assignment exists in the server , calling the create function
            printf("\n\tNo such assignment exists on your local machine , Creating it from the server\n\n");
            createassignment(serverPath,assignment);
        }

    }
    else // the assignment exists in the local machine
    {
        chdir(assignment->str);
        String *get = make_empty_String();
        sprintf(get->str, "find . -type f -name '*.pdf' > pdfNames.txt");
        system(get->str);

        FILE* fp = fopen("pdfNames.txt","r");
        String *dummyString = make_empty_String();
        size_t stringLength = 0;
        ssize_t readFile;

        int numberOfLines = countLines(*make_String("pdfNames.txt"));

        for(int i = 0; i < numberOfLines ; i++)
        {
            char pdfName[100];
            fscanf(fp, "%s" , pdfName);
            String *pdfname = make_String(&pdfName[2]); // Deletes all the files before copying over
            deleteFile(*pdfname);
        }
        fclose(fp);
        deleteFile(*make_String("pdfNames.txt")); // Remove temporary file created
        deleteFolder(*make_String("dist")); // Delete the dist folder

        chdir("..");

        String *dist = attach_String(folder->str, "/dist");
        String *command = make_empty_String();

        sprintf(command->str, "find %s/ -name '*.pdf' -exec cp -pr '{}' '%s/' ';'",
                folder->str,
                assignment->str); // finds all the updated pdf files present in server and
        // copies them to assignment
        system(command->str);
        sprintf(
                command->str, "cp -r  %s %s > /dev/null", dist->str,
                assignment->str); // copies the updated dist folder from server into assignment
        system(command->str);
        printf("\n\tAssignment \"%s\" Updated\n\n", assignment->str);

    }


}

void commandUpdate(token_mat args_mat)
{
    if (args_mat.num_args != 1) {
        printf("\n\tInvalid usage of the update command\n\n");
        printf("\tupdate command syntax: update <assignment> \n\n");
    }
    else if (!isInSubject)
    {
        printf("\n\tError: You are not in a Subject yet\n\n");
    }
    else
    {
        String *assignmentName = make_String(args_mat.args[1]);
        String *currsubj = getCurrentSubject();
        String *serverpath = make_String("../../Server/");
        serverpath = attach_String(serverpath->str, currsubj->str);
        updateAssignment(serverpath,assignmentName);
    }

}