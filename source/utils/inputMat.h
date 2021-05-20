#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../globals.h"

typedef struct argMat tokenMat;

struct argMat
{
    char **args;
    int numArgs;

};

tokenMat makeArgsMat();
#endif