#ifndef _EXTERN_H_
#define _EXTERN_H_
#include "cshell.h"

extern char *commands[LINE_SIZE];
extern char *arguments[ARG_SIZE];
extern char *cmd_ptr;
extern char *arg_ptr;

extern CMD *cmd[PIPE_SIZE];

#endif