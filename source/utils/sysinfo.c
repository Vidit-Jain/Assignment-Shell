#include "sysinfo.h"

String getUsername() // gets the username
{
	String *username = makeEmptyString();
	struct passwd *p = getpwuid(getuid());
	strcpy(username->str, p->pw_name);
	username->length = strlen(username->str);

	return *username;
}

String getPwd() // gets the machine name but this isnt used
{
	if (startPoint == 0) {
		subj = makeEmptyString();
		startPoint++;
	}
	String current_path;
	current_path.str = (char *)malloc(sizeof(char) * MAX_TOKEN_LENGTH);
	getcwd(current_path.str, MAX_TOKEN_LENGTH);
	current_path.length = (int)strlen(current_path.str);

	int match = compareString(current_path, homePath);
	if (match >= homePath.length) {
		sprintf(current_path.str, "~%s", homePath.str);
	}
	current_path.length = (int)strlen(current_path.str);
	return current_path;
}

void outPwd() // unused util
{
	String current_path;
	current_path.str = malloc(sizeof(char) * MAX_TOKEN_LENGTH);
	getcwd(current_path.str, MAX_TOKEN_LENGTH);
	printf("%s", current_path.str);
}