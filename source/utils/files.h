#ifndef __FILES_H__
#define __FILES_H__
#include "string.h"

int folderExists(String path);
int fileExists(String path);

int deleteFile(String path);
int deleteFolder(String path);

int createZip(String path, String zipName);
int unzipToDirectory(String zipName, String path);
void folderHash(String assignmentName, String hashName);
void zipHash(String fileName, String hashName);
void ifSubmissionFolder(String assignmentFolder, String *zipfile);

int validFileName(String name);
int countLines(String fileName);
int createFolder(String folder);

void enterSubjectDirectory();

String *getCurrentSubject();
int copyToServer(String *zipfile, String assignmentFolder);

void printError(String message);
void printSuccess(String message);
void printWarning(String message);

void clearScreen();
#endif
