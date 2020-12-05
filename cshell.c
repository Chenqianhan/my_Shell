#include "cshell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

char commands[LINE_SIZE];
char arguments[ARG_SZIE];
char *cmd_ptr;
char *arg_ptr

CMD cmd[PIPE_SIZE];

void handler(int sig){
    printf("\n[MyShell]$ ");
    fflush(stdout);
}

void init(void){
    memset(cmd, 0, sizeof(cmd));
    memset(commands, 0, sizeof(commands));
    memset(arguments, 0, sizeof(arguments));

    cmd_ptr = commands;
    arg_ptr = arguments;

    printf("\n[MyShell]$ ");
    fflush(stdout);
}

void shell(void){
    while(1){
        if(read_cmd() == -1){
            break;
        }

        parse_cmd();
        execute_cmd();
    }
}

/**
 * Match str with commands
 * If succ, return 1 and cmd_ptr save current position
 * Else, return 0 and cmd_ptr stay unchanged.
 **/
int check(const char *str){
    char *tmp;
    while(*cmd_ptr == '\t' || *cmd_ptr == ' '){
        cmd_ptr++;
    }

    tmp = cmd_ptr;
    while(*str != '\0' && *str == *tmp){
        tmp++;
        str++;
    }

    //It means match succeed
    if(*str == '\0'){
            cmd_ptr = tmp;
            return 1;
    }

    return 0;
}

int read_cmd(void){
    if(fgets(commands, LINE_SIZE, stdin) == NULL){
        return -1;
    }

    return 0;
}

int parse_cmd(void){
    if(check("\n")){
        return 0;
    }

    if()
    
}

int main(void){
    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);

}