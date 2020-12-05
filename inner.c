#include "inner.h"
#include "cshell.h"
#include "extern.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>

INNER_CMD inners[] = {
    {"exit", EXIT},
    {"cd", CD},
    {"type", TYPE},
    {"about", ABOUT},
    {"jobs", JOBS},
    {"kill", KILL},
    {NULL, NULL}
};

int is_inner(void){
    int idx = 0, isFound = 0;
    while(inners[idx].name != NULL){
        if(check(inners[idx].name)){
            inners[idx].inner_func();
            isFound = 1;
            break;
        }
    }

    return isFound;
}



