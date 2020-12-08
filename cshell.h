#ifndef _CSHELL_H_
#define _CSHELL_H_

#define LINE_SIZE 128 // Maximum length of input
#define ARG_SIZE 20 // Maximum number of arguments in a single command
#define PIPE_SIZE 2 // Maximum number of command in pipe
#define NAME_SIZE 100 // Maximum length of IO filename in redirection.
#define OPEN_MAX 1024

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } \
    while(0) 
//ls -l, cmd[0].arg[0] = ls, cmd[0].arg[1] = -l;
//cd, cmd[0].arg[0] = cd, cmd[0].arg[1] = null
//ls -l;cd\n
typedef struct cmd{
    char *args[ARG_SIZE];
    int input;
    int output;
}CMD;
/*
typedef struct job{
    pid_t pid;
    char *back[30];
    struct job *next;
}JOB;
*/
typedef void (*INNER_FUNC)(void);

typedef struct inner_cmd{
    char *name;
    INNER_FUNC inner_func;
}INNER_CMD;

//-----------Core-----------------
void init(void);
void shell(void);
void handler(int sig);

//-----------Command----------------
int check(const char *str);
void get_cmd(int i);
void get_string(char *name);
int read_cmd(void);
int parse_cmd(void);
void execute_cmd(int cmd_cnt);
void fork_exec(int i);

//-----------Inner func------------
int is_inner(void);
void run_inner(int idx);
void EXIT(void);
void CD(void);
void PWD(void);

#endif