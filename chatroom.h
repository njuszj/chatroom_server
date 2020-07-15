# ifndef CHATROOM_H
# define CHATROOM_H
# include "tcp_services.h"
# include "environment.h"

# define MAX_CONNECTED_CLIENT_NUM 100
# define RECV_BUFFSIZE 4096

extern Logger logger;

class Chatroom{
    // 聊天室服务端主体
public:
    Chatroom();// 构造函数
    ~Chatroom();// 析构函数
    void startListen();//开始监听端口接受请求
    void freeIndexs(int index);
private:
    TcpServer tcp_manager;
    stack<int> s_indexs;  // 使用栈管理可用的下标
    int connects[MAX_CONNECTED_CLIENT_NUM];
    pthread_t tids[MAX_CONNECTED_CLIENT_NUM];
    int socket_id;
};

void* process(void* arg); //处理函数
struct ProcessArg{
    // process 函数的传入参数
    int index;
    int cid;
    Chatroom* ct;
    ProcessArg(int, int, Chatroom*);
};

# endif