#ifndef __FILES_H__
#define __FILES_H__
#include "string.h"
#include <dirent.h>

int folderExists(String path);
int fileExists(String path);

int deleteFile(String path);
int deleteFolder(String path);

int createZip(String path, String zipName);
int unzipToDirectory(String zipName, String path);
void folderHash(String assignmentName, String hashName);
void zipHash(String fileName, String hashName);
String *find_zip(String *file);
void IFsubmission_folder(String assignment_folder, String *zipfile);

int validFileName(String name);
int countLines(String fileName);
int createFolder(String folder);

void enterSubjectDirectory();

String *getCurrentSubject();
void get_serverpath();
int copy_to_server(String *zipfile, String assignment_folder);
int zipexists(String folder);
#endif
