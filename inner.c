#include "inner.h"
#include "cshell.h"
#include "extern.h"


INNER_CMD inners[] = {
    {"exit", EXIT},
    {"cd", CD},
    {"type", TYPE},
    {"about", ABOUT},
    {"jobs", JOBS},
    {"kill", KILL},
    {NULL, NULL}
};

//-1 means no inner func
int is_inner(void){
    int idx = 0, inner_id = -1;
    while(inners[idx].name != NULL){
        if(check(inners[idx].name)){
            inner_id = idx;
            break;
        }
    }

    return inner_id;
}

void run_inner(int idx){
    inners[idx].inner_func();
    
    return;
}



