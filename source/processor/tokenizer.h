#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../utils/inputMat.h"
#include "input.h"

void tokenizeInput(String Input);
void execute(tokenMat argsMat);

#endif

