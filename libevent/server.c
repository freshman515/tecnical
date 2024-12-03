#include <stdio.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
//所有的io ，都是非阻塞i o，libevent异步事件库
#include <hiredis/hiredis.h>
#include <hiredis/adapters/libevent.h> //配置hiredis和libevent的适配器
#include <hiredis/async.h>
#include <string.h>
#include "imp.h"
#include <stdlib.h>
redisAsyncContext* redis_conn;
#define PORT 8989
void connectCallback(const redisAsyncContext* c, int status) {
    if (status != REDIS_OK) {
        printf("Error = %s\n", c->errstr);
        return;
    }
    printf("redis Connected successful!\n");
}
void disconnectCallback(const redisAsyncContext* c, int status) {
    if (status != REDIS_OK) {
        printf("Error = %s\n", c->errstr);
        return;
    }
    printf("redis Disconnected...\n");
}
static void on_read(struct buffervent* bev, void* arg) {
    //得到输入缓冲区
    struct evbuffer* evbuf = bufferevent_get_input(bev);
    //从缓冲区读取一个完整的数据包数据
    char* msg = evbuffer_readln(evbuf, NULL, EVBUFFER_EOL_CRLF);
    if (!msg) {
        return;
    }
    Arg* args = split_req(msg);
    printf("args->len=%d args->eles = %d command =%s\n", args->len, args->eles, args->str);
    if (args->eles == 2) {
        printf("param1 = %s, param2 = %s\n", args->next->str, args->next->next->str);
    }
    Command* cmd = get_command(args->str);
    if (cmd == NULL) {
        printf("invalid command: %s\n", args->str);
        free(args);
        return;
    }
    cmd->proc(bev, args);

    free(msg);
}
static void on_error(struct bufferevent* bev, short events, void* arg) {
    if (events & BEV_EVENT_EOF) {
        printf("connection close\n");
    } else if (events & BEV_EVENT_ERROR) {
        printf("some other error ");
    } else if (events & BEV_EVENT_TIMEOUT) {
        printf("timeout ");
    }
    bufferevent_free(bev);
}
//建立连接的回调函数
static void on_open(struct evconnlistener* listener,
    evutil_socket_t fd,
    struct sockaddr* sock,
    int socklen,
    void* arg) {
    char ip[32] = { 0 };
    evutil_inet_ntop(AF_INET, sock, ip, sizeof(ip) - 1);
    printf("accept client ip = %s,fd= %d\n", ip, fd);
    struct event_base* base = (struct event_base*)arg;
    //注册fd事件
    struct bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    //注册读事件
    bufferevent_setcb(bev, on_read, NULL, on_error, NULL);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);
}
int main() {
    struct event_base* base = event_base_new(); // 创建事件管理器管理对象
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(struct sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    // 创建监听者
    struct evconnlistener* listener = evconnlistener_new_bind(base, on_open, base, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
        512, (void*)&sin, sizeof(sin));
    printf("server listen port : %d\n", PORT);

    //redis 建立连接
    redisOptions options = { 0 };
    REDIS_OPTIONS_SET_TCP(&options, "127.0.0.1", 6379);
    struct timeval tv = { 0 };
    tv.tv_sec = 1;
    options.connect_timeout = &tv;
    redis_conn = redisAsyncConnectWithOptions(&options);
    if (redis_conn->err) {
        printf("Error:%s\n", redis_conn->errstr);
        return 1;
    }
    //redis和libevent库进行绑定   因为所有网络流程都是通过libevent进行管理
    redisLibeventAttach(redis_conn, base);
    //连接建立成功的回调
    redisAsyncSetConnectCallback(redis_conn, connectCallback);
    //连接建立失败的回调
    redisAsyncSetDisconnectCallback(redis_conn, disconnectCallback);
    event_base_dispatch(base);

    event_base_free(base);
}