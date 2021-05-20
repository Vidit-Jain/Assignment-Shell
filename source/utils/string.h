#ifndef __STRING_H__
#define __STRING_H__

#include "../processor/input.h"
#include "../globals.h"

// Basic functions

String *makeEmptyString();
String *copyString(String *dest, String *src);
String *breakString(String src, int break_len);
String *makeString(const char *src);
int compareString(String str1, String str2);
String eraseString(String x);

// utility function 

String *attachString(char *x, char *y);

#endif