#include "commands/execvp.h"
#include "processor/input.h"
#include "processor/prompt.h"
#include "processor/tokenizer.h"
#include "utils/files.h"
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
	for (int i = 0; i < serverFileCount; i++) {
		createFolder(subjectArray[i]);
	}

	while (1) {
		initialize();
		String input;
		prompt_print();
		i = 0;
		char temp;
		input.str = (char *)malloc(sizeof(char) * MAX_TOKEN_LENGTH);
		while (1) {
			temp = (char)getchar();
			if (temp != '\n')
				input.str[i++] = temp;
			else {
				input.str[i] = '\0';
				break;
			}
		}

		tokenizeInput(input);
	}
}
