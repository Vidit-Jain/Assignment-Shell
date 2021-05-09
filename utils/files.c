#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <regex.h>
#include "files.h"
#include "string.h"

#define MAX_LEN 2000

// Takes in a path and verifies if such a folder exists
int folderExists(String path)
{
	struct stat sb;
	return stat(path.str, &sb) == 0 && S_ISDIR(sb.st_mode);
}

// Takes in a path and verifies if such a file exists
int fileExists(String path)
{
	struct stat sb;
	return stat(path.str, &sb) == 0 && S_ISREG(sb.st_mode);
}

/* Deletes the file specified by the path
 * Returns 0 if it doesn't exist
 * Returns 1 if it does and deletes the file
 */
int deleteFile(String path)
{
	if (!fileExists(path))
	{
		return 0;
	}
	String *command = make_empty_String();
	sprintf(command->str, "rm %s > /dev/null", path.str);
	system(command->str);
	return 1;
}

/* Deletes the folder specified by the path
 * Returns 0 if it doesn't exist
 * Returns 1 if it does and deletes the folder
 */
int deleteFolder(String path)
{
	if (!folderExists(path))
	{
		return 0;
	}
	String *command = make_empty_String();
	sprintf(command->str, "rm -r %s > /dev/null", path.str);
	system(command->str);
	return 1;
}

String *find_zip(String *file)
{
	if (fileExists(*file))
	{
		return file;
	}
}

/* Zips a folder specified by path
 * Returns 0 if the folder doesn't exist
 * Returns 1 if the folder exists and you create a zip with the name as zipName
 */
int createZip(String path, String zipName)
{
	if (!folderExists(path))
	{
		return 0;
	}
	String *command = make_empty_String();
	sprintf(command->str, "zip -r %s.zip %s > /dev/null", zipName.str, path.str);
	system(command->str);
	return 1;
}

/* Unzips a zip file to a path specified
 * Returns 0 if the zip files doesn't exist
 * Returns 1 if it does and is unzipped
 */
int unzipToDirectory(String zipName, String path)  {
    if (!fileExists(zipName)){
        return 0;
    }
    String* command = make_empty_String();
    sprintf(command->str, "unzip %s -d %s > /dev/null", zipName.str, path.str);
    system(command->str);
    return 1;
}

/* Creates a folder at path specified
 * Returns 0 if the folder already exists
 * Else it returns 1 and creates the folder
 */
int createFolder(String folder)
{
	if (folderExists(folder))
	{
		return 0;
	}

	String *command = make_empty_String();
	sprintf(command->str, "mkdir %s > /dev/null", folder.str);
	system(command->str);
	return 1;
}
/* Uses regex to verify if the given name is a valid file name
 * We've restricted the file names intentionally, so you might be able to make
 * file names with some symbols normally but wouldn't pass validFileName as we only want
 * more standard symbols for files to be permitted
 */
int validFileName(String name)
{
	String *fileRegex = make_String("[^-_.A-Za-z0-9]");
	regex_t regex;
	int value = regcomp(&regex, fileRegex->str, 0);
	value = regexec(&regex, name.str, 0, NULL, 0) == 0;
	return !value;
}

// Opens a file and returns the number of lines in it, returns -1 if it doesn't exist
int countLines(String fileName)
{

	if (!fileExists(fileName))
		return -1;

	FILE *fp = fopen(fileName.str, "r");

	String *dummyString = make_empty_String();
	size_t stringLength = 0;
	ssize_t readFile;

	int numberOfLines = 0;

	while ((readFile = getline(&(dummyString->str), &stringLength, fp)) != -1)
	{
		numberOfLines++;
	}
	fclose(fp);

	return numberOfLines;
}

String *getCurrentSubject()
{
	String *homePath;
	homePath = make_empty_String();

	getcwd(homePath->str, MAX_LEN);
	int strLen = strlen(homePath->str);
	String *currSubject = make_empty_String();

	char *token;
	token = strtok(homePath->str, "/");
	String *prev = make_empty_String();

	if (isInSubject)
	{
		while (token != NULL)
		{
			strcpy(prev->str, token);
			token = strtok(NULL, "/");
		}
	}

	for (int i = 0; i < Server_file_count; i++)
	{
		if (strcmp(prev->str, Subject_array[i].str) == 0)
			return prev;
	}

	strcpy(prev->str, "");
	return prev;
}

// Enters the subject directory when you start the shell
void enterSubjectDirectory()
{
	chdir("Subjects");
	printf("Enter switch <subject_name> to begin\n");
}

void IFsubmission_folder(String assignment_folder, String *zipfile)
{
	String *submission_folder;

	submission_folder = make_String("../../Server/");
	submission_folder = attach_String(submission_folder->str, getCurrentSubject()->str);
	submission_folder = attach_String(submission_folder->str, "/");
	submission_folder = attach_String(submission_folder->str, assignment_folder.str);
	submission_folder = attach_String(submission_folder->str, "/submissions");

	if (!folderExists(*submission_folder))
	{
		createFolder(*submission_folder);
	}
}

int zipexists(String folder)
{
	DIR *d;
	struct dirent *dir;
	d = opendir("../Server");

	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
			{
				if (strcmp(folder.str, dir->d_name) == 0)
				{
					return 1;
				}
			}
		}

		closedir(d);
	}
	return 0;
}

int copy_to_server(String *zipfile, String assignment_folder)
{
	String *home_path = make_empty_String();

	getcwd(home_path->str, MAX_LEN);

	String *path = make_empty_String();
	path->str = "../../Server/";

	path = attach_String(path->str, getCurrentSubject()->str);
	path = attach_String(path->str, "/");
	path = attach_String(path->str, assignment_folder.str);
	path = attach_String(path->str, "/submissions/");

	path = attach_String(path->str, zipfile->str);

	if (fileExists(*zipfile))
	{
		while (1)
		{
			String* prompt = make_empty_String();
			printf("\n\tThe zip file already exists!\n\tEnter Overwrite to replace existing file or Return to leave as it is: ");
            int i = 0;
            char temp;
            while (1)
            {
                temp = (char)getchar();
                if (temp != '\n')
                    prompt->str[i++] = temp;
                else
                {
                    prompt->str[i] = '\0';
                    break;
                }
            }

			if (strcmp(prompt->str, "Overwrite") == 0)
			{
				deleteFile(*path);
				String *command = make_empty_String();

				sprintf(command->str, "cp %s %s > /dev/null", zipfile->str, path->str);
				system(command->str);
				return 1;
			}
			else if (strcmp(prompt->str, "Return") == 0)
			{
				return 0;
			}
			else
			{
				printf("\n\tWrong Command, please enter again!\n\n");
			}
		}
	}
	else
	{
		String *command = make_empty_String();

		sprintf(command->str, "cp %s %s > /dev/null", zipfile->str, path->str);

		system(command->str);
		return 1;
	}
}
