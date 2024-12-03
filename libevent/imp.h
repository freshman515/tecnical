#ifndef _LIB_LOGIN_H
#define _LIB_LOGIN_H
#include <string.h>
typedef struct Arg {
    size_t len;
    char* str;
    size_t eles;
    struct Arg* next;
}Arg;

typedef void (*CommandProc)(struct bufferevent*, struct Arg*);

typedef struct Command {
    char* name;
    CommandProc proc;
    char* desc;
}Command;

//把完整的数据包分割成链表Arg
Arg* split_req(char* msg);

void free_req(Arg*);

struct Command* get_command(const char*);

#endif