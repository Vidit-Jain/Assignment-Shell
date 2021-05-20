#ifndef __SYS_INFO_H__
#define __SYS_INFO_H__

#include <fcntl.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "string.h"
#include "../globals.h"
#include "../processor/input.h"

String getUsername();
String getPwd();
void outPwd();

#endif