#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "../utils/inputMat.h"
#include "../utils/string.h"
void createAssignment(String *serverPath, String *assignment);

void commandCompare(tokenMat argsMat);
void commandCreate(tokenMat argsMat);
void commandSetup(tokenMat argsMat);
void commandSubmit(tokenMat argsMat);
void commandSwitch(tokenMat argsMat);
void commandTest(tokenMat argsMat);
void commandTree(tokenMat argsMat);
void commandUpdate(tokenMat argsMat);
void commandUse(tokenMat argsMat);
void commandList(tokenMat argsMat);

#endif
