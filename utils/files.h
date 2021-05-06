#ifndef __FILES_H__
#define __FILES_H__
#include "string.h"

int folderExists(String path);
int fileExists(String path);

int deleteFile(String path);
int deleteFolder(String path);

int createZip(String path, String zipName);
String *find_zip(String *file);

int validFileName(String name);
int countLines(String fileName);
int createFolder(String folder);

void enterSubjectDirectory();

String *getCurrentSubject();
void get_serverpath();
int copy_to_server(String *zipfile);
#endif
