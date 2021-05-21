#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "utils/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAX_NUM_OF_TOKENS 20
#define MAX_TOKEN_LENGTH 100

extern int startPoint;
extern int isInSubject;

extern String homePath;
extern String prevPath;

extern int serverFileCount;
extern String *subjectArray; // stores all the subject names

extern int useCond;
extern String *useAssignmentName; // stores the Assignment name

#define BOLD "\033[1m"
#define NO_BOLD "\033[22m"
#define RED "\033[38;5;1m"
#define GREEN "\033[38;5;121m"
#define ORANGE "\033[38;5;209m"
#define PURPLE "\033[38;5;205m"
#define LIGHT_PINK "\033[38;5;225m"
#define LIGHT_PURPLE "\033[38;5;213m"
#define YELLOW "\033[38;5;223m"
#define RESET "\033[0m"
#define BLUE "\033[0;34m"

#endif
