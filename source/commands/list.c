#include "../utils/files.h"
#include "commands.h"
void commandList(tokenMat argsMat) {
	if (argsMat.numArgs != 0) {
		String *error =
			makeString("\n\tERROR: Invalid usage of the list command\n\n\tlist "
					   "command syntax: list\n\n");
		printError(*error);
	} else {
		system("ls");
	}
}