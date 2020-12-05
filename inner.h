#ifndef _INNER_H_
#define _INNER_H_

typedef void (*INNER_FUNC)(void);

typedef struct inner_cmd{
    char *name;
    INNER_FUNC inner_func;
}INNER_CMD;

int is_inner(void);
void EXIT(void);
void CD(void);
void TYPE(void);
void ABOUT(void);
void JOBS(void);
void KILL(void);

#endif