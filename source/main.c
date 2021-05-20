#include "processor/input.h"
#include "processor/prompt.h"
#include "processor/tokenizer.h"
#include "utils/files.h"
#include "commands/execvp.h"
#include "utils/Subjects.h"

int main()
{
    clearScreen();
    start_point = 0;
    UseCond = 0;
    int i;

    // Creates Subjects folder if it doesn't exist
    String *subjectString = make_String("Subjects");
    createFolder(*subjectString);

    enterSubjectDirectory();
    Initialize_subject_array();
    for (int i = 0; i < Server_file_count; i++) {
        createFolder(Subject_array[i]);
    }
    while (1)
    {
        Initialize();
        String Input;
        prompt_print();
        i = 0;
        char temp;
        Input.str = (char *)malloc(sizeof(char) * MAX_TOKEN_LENGTH);
        while (1)
        {
            temp = (char)getchar();
            if (temp != '\n')
                Input.str[i++] = temp;
            else
            {
                Input.str[i] = '\0';
                break;
            }
        }

        tokenize_input(Input);
    }
}
