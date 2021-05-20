//used to keep an array of subject names
#include "subjects.h"
void initializeSubjectArray()
{

    DIR *d;
    struct dirent *dir;
    d = opendir("../Server");

    serverFileCount = 0;

    if (d) //gets us the number of subjects
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                serverFileCount++;
            }
        }

        closedir(d);
    }
    subjectArray = malloc(sizeof(String) * serverFileCount);
    for (int i = 0; i < serverFileCount; i++)
    {
        subjectArray[i].str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
    }
    d = opendir("../Server");

    if (d)
    {
        int i = 0;
        while ((dir = readdir(d)) != NULL) 
        {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                strcpy(subjectArray[i].str, dir->d_name);  //stores the subject name
                subjectArray[i].length = strlen(subjectArray[i].str);

                i++;
            }
        }
        closedir(d);
    }
}
