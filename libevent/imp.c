#include "imp.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <event2/bufferevent.h>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>

extern redisAsyncContext* redis_conn;
void on_login(struct bufferevent* bev, struct Arg* args);
void on_heartbeat(struct bufferevent* bev, struct Arg* args);

typedef struct ReplyContext {
    struct bufferevent* bev;   //代表具体的连接
    struct Arg* args;   //具体的参数
}replyContext;

struct Command commandTable[] = {
    {"login",on_login,"login: please provide name and password"},
    {"heart",on_heartbeat,"heart: heart beat"},
};
void callback(redisAsyncContext* c, void* r, void* privdata) {
    redisReply* reply = r;
    if (reply == NULL) return;
    if (reply->type == REDIS_REPLY_ERROR) {
        printf("Error: %s\n", reply->str);
    } else if (reply->type == REDIS_REPLY_STRING) {
        printf("Value: %s\n", reply->str);
    } else if (reply->type == REDIS_REPLY_NIL) {
        printf("Key does not exist.\n");
    } else if (reply->type == REDIS_REPLY_STATUS) {
        printf("redis: %s\n", reply->str);
    } else {
        printf("Unexpected reply type: %d\n", reply->type);
    }
}
void redis_login_hget(redisAsyncContext* c, void* r, void* privdata) {
    redisReply* reply = r; // redis给我们返回的值就在reply当中
    printf("redis_login_hget type:%d\n", reply->type);

    replyContext* rc = (replyContext*)privdata;
    if (reply->element == 0) {
        Arg* temp = rc->args->next;
        const char* name = temp->str;
        temp = temp->next;
        const char* passwd = temp->str;
        printf("33 name %s passwd %s\n", name, passwd);
        char* keys = "str1";
        redisAsyncCommand(redis_conn, callback, privdata, "HMSET role:%s name %s passwd %s", name, name, passwd);
        char* str = "注册成功\n";
        bufferevent_write(rc->bev, str, strlen(str));
    } else {
        char* str = "登陆成功\n";
        bufferevent_write(rc->bev, str, strlen(str));

    }
    free(rc->args);
    free(rc);

    //if没有用户，注册用户
    //if纯在，用户数返回客户端



}

Arg* split_req(char* msg) {
    char* temp = strtok(msg, " ");
    if (!temp) return NULL;
    Arg* req = (Arg*)malloc(sizeof(*req));
    if (!req) return NULL;
    req->len = strlen(temp);
    req->str = (char*)malloc(req->len + 1);
    if (!req->str) return NULL;
    memset(req->str, 0, req->len + 1);
    strncpy(req->str, temp, strlen(temp));
    req->eles = 0;
    Arg* tail = req;
    //继续从上次分割的地方分割字符串
    while (temp = strtok(NULL, " ")) {
        Arg* ele = (Arg*)malloc(sizeof(*ele));
        if (!ele) return NULL;
        ele->len = strlen(temp);
        ele->str = (char*)malloc(ele->len + 1);
        if (!ele->str) return NULL;
        memset(ele->str, 0, ele->len + 1);
        strncpy(ele->str, temp, strlen(temp));
        tail->next = ele;
        ele->next = NULL;
        tail = ele;
        req->eles++;
    }
    return req;
}
void free_req(Arg*) {

}

struct Command* get_command(const char* cmd) {
    int numcommands = sizeof(commandTable) / sizeof(Command);
    for (int i = 0;i < numcommands;i++) {
        Command* c = commandTable + i;
        if (strcmp(c->name, cmd) == 0) {
            return c;
        }
    }
    return NULL;
}
static void reply_error(struct bufferevent* bev, const char* errstr) {
    printf("%s\n", errstr);
    //发数据给客户端
    bufferevent_write(bev, errstr, strlen(errstr));
}
void on_login(struct bufferevent* bev, struct Arg* args) {
    printf("call on_login()\n");
    if (args->eles < 2) {
        //把错误返回给客户端
        reply_error(bev, "on_login parameter error");
        return;
    }
    Arg* params = args->next;
    const char* name = params->str;
    size_t name_len = params->len;
    params = params->next;
    const char* passwd = params->str;
    size_t passwd_len = params->len;
    printf("name = %s passwd = %s\n", name, passwd);

    replyContext* reply = malloc(sizeof(*reply));
    reply->bev = bev;
    reply->args = args;
    //redis返回的时候，会回到redis_login_hget方法       
    redisAsyncCommand(redis_conn, redis_login_hget, reply, "hgetall role:%s", name);

}
void on_heartbeat(struct bufferevent* bev, struct Arg* args) {
    printf("call on_heartbeat()\n");
}