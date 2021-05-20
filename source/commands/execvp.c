#include "commands.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../globals.h"
#include "../processor/prompt.h"
#include "../utils/inputMat.h"

void exec(tokenMat args_mat)
{

	int child = fork();

	if (child == -1) {
		perror("Could not fork child");
	}
	else if (child == 0) {

		if (execvp(args_mat.args[0], args_mat.args) < 0) {
			perror("System Command Execution Terminated Unexpectedly");
			exit(1);
		}
		exit(0);
	}
	else {

		usleep(100000);
	}
}