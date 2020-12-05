#ifndef _CSHELL_H_
#define _CSHELL_H_

#define LINE_SIZE 1024 // Maximum length of input
#define ARG_SIZE 20 // Maximum number of arguments in a single command
#define PIPE_SIZE 10 // Maximum number of command in pipe
#define NAME_SIZE 100 // Maximum length of IO filename in redirection.
#define OPEN_MAX 1024

typedef struct cmd{
    char *args[ARG_SIZE];
    int input;
    int output;
}CMD;


#endif