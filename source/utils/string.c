#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../globals.h"
#include "string.h"

#define MAX_LEN 2000

/* This function creates a struct pointer variable , allocates it space
   and return the pointer to struct
*/
String *makeEmptyString() {
	String *empty;
	empty = (String *)malloc(sizeof(String));
	empty->str = (char *)malloc(sizeof(char) * 200);

	return empty;
}

/* This function erases a string in the sense that
	it removes the characters it had and makes it length = 0,
	making it re-usable without again allocating space
*/
String eraseString(String x) {
	x.str[0] = '\0';

	x.length = 1;

	return x;
}

/* Makes a input String into newly created String data-type
	such that it also stores it length for faster access to it
	at later occurrences.
*/
String *makeString(const char *src) {
	String *data = makeEmptyString();

	data->length = strlen(src) + 1;

	strncpy(data->str, src, data->length);

	return data;
}

/* This function copies a struct String pointer to another inorder
	to use struct's functionalities later
*/
String *copyString(String *dest, String *src) {
	dest = makeEmptyString();

	dest->length = src->length;

	strncpy(dest->str, src->str, src->length);

	return dest;
}
/* This function compares 2 struct String such that
	returns index till which both strings are same, i.e.,
	if both are equal then returns min(strlen1.strlen2)
	else returns index till which they are same
*/
int compareString(String str1, String str2) {
	int i;

	for (i = 0; i < str1.length && i < str2.length; i++) {
		if (str1.str[i] != str2.str[i]) {
			return i;
		}
	}

	return (int)fmin(str1.length, str2.length);
}

/* This function takes a index as input at which the string
	should be broken at,i.e, the characters after that index
	are replaced with just a \0"
*/
String *breakString(String src, int break_len) {
	String *dest = makeEmptyString();

	dest->length = break_len + 1;

	if (src.length >= break_len)
		strncpy(dest->str, src.str, break_len);

	return dest;
}

/* This function is a helpful one as it takes 2 input strings and
	attaches them to form a single string and then also stores it
	in the struct string pointer and returns it such that it can be
	used easily at later occurrences.
*/
String *attachString(char *x, char *y) {
	String *attached;

	attached = makeString(x);

	attached->str = strcat(attached->str, y);

	attached->length = strlen(attached->str) + 1;

	return attached;
}
