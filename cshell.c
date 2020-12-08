#include "cshell.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/limits.h>
/**
 * exit works
 * ls and cd didn't work
 * after one command, it doesn't work and show myShell
 **/

char commands[LINE_SIZE];
char arguments[ARG_SIZE];
char output_file[NAME_SIZE];
char *cmd_ptr;
char *arg_ptr;
char cwd[NAME_SIZE];

CMD cmd[PIPE_SIZE];
int is_append;
int has_next;
//int is_main;
//JOB *head;

INNER_CMD inners[] = {
    {"exit", EXIT},
    {"cd", CD},
    {"pwd", PWD},
    {NULL, NULL}
};

void handler(int sig){
    //printf("\n%s $ ", cwd);
    fflush(stdout);
    //fflush(stdin);
    return;
}

void init(void){
    memset(cmd, 0, sizeof(cmd));
    memset(commands, 0, sizeof(commands));
    memset(arguments, 0, sizeof(arguments));
    memset(output_file, 0, sizeof(output_file));
    for(int i=0;i<PIPE_SIZE;i++){
        cmd[i].input = 0;
        cmd[i].output = 1;
    }

    is_append = 0;
    //is_main = 0;
    has_next = 0;
    cmd_ptr = commands;
    arg_ptr = arguments;

    getcwd(cwd, sizeof(cwd));

    printf("\n%s $ ", cwd);
    fflush(stdout);
    //fflush(stdin);
}

void shell(void){
    //int status = 1;
    while(1){
        init();
        
        //printf("Reading cmd\n");
        if(read_cmd() == -1){
            break;
        }

        //printf("Parsing cmd\n");
        int cmd_cnt = parse_cmd();
        //printf("Execute_cmd\n");
        execute_cmd(cmd_cnt);
        
        while(has_next){
            //memset(cmd, 0, sizeof(cmd));
            memset(output_file, 0, sizeof(output_file));
            is_append = 0;

            cmd_cnt = parse_cmd();
            execute_cmd(cmd_cnt);
        }
        
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

/**
 * Put command into cmd
 * Put parameters into arguments
 **/
void get_cmd(int i){
    int arg_idx = 0, isWord;

    while(*cmd_ptr != '\0'){
        while(*cmd_ptr == ' ' || *cmd_ptr == '\t'){
            cmd_ptr++;
        }
        cmd[i].args[arg_idx] = arg_ptr;
        while(*cmd_ptr != '\0' 
            && *cmd_ptr != ' '
            && *cmd_ptr != '\t'
            && *cmd_ptr != '>'
            && *cmd_ptr != '|'
            && *cmd_ptr != '\n'
            && *cmd_ptr != ';'
            ){
                *arg_ptr++ = *cmd_ptr++;
                isWord++;
            }
        *arg_ptr++ = '\0';
        cmd[i].args[arg_idx + 1] = NULL;
        /*
        if(*cmd_ptr == '\n'){
            if(isWord == 0){
                cmd[i].args[arg_idx] = NULL;
            }
            return;
        }
        */
       switch(*cmd_ptr){
            case ' ':
                    isWord = 0;
                    arg_idx++;                        
                    break;
            case '\t':
                    isWord = 0;
                    arg_idx++;                        
                    break;
            case '>':
            case '|':
            case ';':
            case '\n':
                    if(isWord == 0) cmd[i].args[arg_idx] = NULL;
                    return;
            default:
                    return;
        }
    }


}

void get_string(char *name){
    while(*cmd_ptr == ' ' || *cmd_ptr == '\t'){
        cmd_ptr++;
    }

    while(*cmd_ptr != '\0' 
            && *cmd_ptr != ' '
            && *cmd_ptr != '\t'
            && *cmd_ptr != '>'
            && *cmd_ptr != '|'
            && *cmd_ptr != '\n'
            && *cmd_ptr != ';'
            ){
                *name++ = *cmd_ptr++;
            }
    *name = '\0';
}

int read_cmd(void){
    if(fgets(commands, LINE_SIZE-1, stdin) == NULL){
        return -1;
    }

    return 0;
}

int parse_cmd(void){
    if(check("\n")){
        return 0;
    }

    int inner_id = is_inner();
    if(inner_id != -1){
        run_inner(inner_id);
        return 0;
    }

    get_cmd(0);
    if(check(">")){
        if(check(">")){
            is_append = 1;
        }
        get_string(output_file);
    }

    int cmd_num = 1;
    if(check("|")){
        get_cmd(1);
        cmd_num++;
    }
    
    if(check("\n")){
        has_next = 0;
        return cmd_num;
    }
    //ls; ls
    if(check(";")){
        has_next = 1;
        return cmd_num;
    }else{
        printf("Command error");
        return -1;
    }
}

void execute_cmd(int cmd_cnt){
    if(!cmd_cnt){
        return;
    }
    
    if(output_file[0] != '\0'){
        if(is_append){
            cmd[cmd_cnt-1].output = open(output_file, O_WRONLY 
            | O_CREAT | O_APPEND, 0666);
        }else{
            cmd[cmd_cnt-1].output = open(output_file, O_WRONLY 
            | O_CREAT | O_APPEND, 0666);
        }
    }
    
    int fd[2];
    for(int i=0;i<cmd_cnt;i++){
        if(i<cmd_cnt-1){
            pipe(fd);
            cmd[i].output = fd[1];
            cmd[i+1].input = fd[0];
        }

        fork_exec(i);

        if(cmd[i].input != 0){
            close(cmd[i].input);
        }

        if(cmd[i].output != 1){
            close(cmd[i].output);
        }
    }
    /*
    if(cmd_cnt > 1){
        pipe(fd);
        cmd[0].output = fd[1];
        cmd[1].input = fd[0];
    }

    for(int i=0;i<cmd_cnt;i++){
        fork_exec(i);
        
        if(cmd[i].input != 0){
            close(cmd[i].input);
        }

        if(cmd[i].output != 1){
            close(cmd[i].output);
        }
        
    }
    */
    return;
}

void fork_exec(int i){
    pid_t pid = fork();
    if(pid == -1){
        ERR_EXIT("fork error");
    }

    if(pid == 0){
        //Child
        //printf("Kid running\n");
        if(cmd[i].input != 0){
            close(0);
            dup(cmd[i].input);
        }

        if(cmd[i].output != 1){
            close(1);
            dup(cmd[i].output);
        }

        //signal(SIGQUIT, SIG_DFL);
        //signal(SIGINT,SIG_DFL);
        execvp(cmd[i].args[0], cmd[i].args);

        exit(EXIT_FAILURE);
    }else{
        //printf("DAD running\n");
        //usleep(800);
        int status = 0;
        wait(&status);
    }
}

//-1 means no inner func
int is_inner(void){
    int idx = 0, inner_id = -1;
    while(inners[idx].name != NULL){
        if(check(inners[idx].name)){
            inner_id = idx;
            break;
        }
        idx++;
    }

    return inner_id;
}

void run_inner(int idx){
    inners[idx].inner_func();
    
    return;
}

void CD(void){
    get_cmd(0);
    int fd;
    fd = open(*(cmd[0].args), O_RDONLY);
    fchdir(fd);
    close(fd);
    
   //chdir(cmd[0].args[0]);
}

void EXIT(void){
    exit(EXIT_SUCCESS);
}

void PWD(void){
    char pos[NAME_SIZE];
    puts(getcwd(pos, NAME_SIZE));
}

int main(void){
    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
    //head = (JOB*)malloc(sizeof(JOB));
    //head->next = NULL;

    shell();

    return 0;
}