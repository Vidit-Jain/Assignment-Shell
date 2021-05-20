#ifndef __SYS_INFO_H__
#define __SYS_INFO_H__

#include <fcntl.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../globals.h"
#include "../processor/input.h"
#include "string.h"

String getUsername();
String getPwd();
void outPwd();

#endif