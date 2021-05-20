#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "../globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct argMat tokenMat;

struct argMat {
	char **args;
	int numArgs;
};

tokenMat makeArgsMat();
#endif