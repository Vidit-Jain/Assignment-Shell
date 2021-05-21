#include "processor/prompt.h"
#include "processor/tokenizer.h"
#include "utils/files.h"
#include "utils/string.h"
#include "utils/subjects.h"

int main()
{
	clearScreen();
	startPoint = 0;
	useCond = 0;
	int i;

	// Creates Subjects folder if it doesn't exist
	String *subjectString = makeString("Subjects");
	createFolder(*subjectString);

	enterSubjectDirectory();
	initializeSubjectArray();

	// Creates all the subject subdirectories that are present in the server
	for (int i = 0; i < serverFileCount; i++) {
		createFolder(subjectArray[i]);
	}

	while (1) {
		initialize();
		promptPrint();

		char temp;
		String *input = makeEmptyString();
		i = 0;
		while (1) {
			temp = (char)getchar();
			if (temp != '\n')
				input->str[i++] = temp;
			else {
				input->str[i] = '\0';
				break;
			}
		}

		tokenizeInput(*input);
	}
}
