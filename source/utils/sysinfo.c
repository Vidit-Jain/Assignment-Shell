#include "sysinfo.h"

String getUsername() // gets the username
{
	String *username = makeEmptyString();
	struct passwd *p = getpwuid(getuid());
	strcpy(username->str, p->pw_name);
	username->length = strlen(username->str);

	return *username;
}