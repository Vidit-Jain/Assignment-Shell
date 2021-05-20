#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "../utils/inputMat.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void tokenizeInput(String Input);
void execute(tokenMat argsMat);

#endif
