# ifndef CHATROOM_H
# define CHATROOM_H
# include "tcp_services.h"
# include "environment.h"
# include <stack>
# include <set>
# include <map>

using std::stack;
using std::set;
using std::map;


# define MAX_CONNECTED_CLIENT_NUM 100
# define RECV_BUFFSIZE 4096
# define SHORT_BUFFSIZE 128

extern Logger logger;

class Chatroom{
    // 聊天室服务端主体
public:
    Chatroom(); // 构造函数
    ~Chatroom();// 析构函数
    void startListen();//开始监听端口接受请求
    void freeIndexs(int index);  // 释放一个资源
    void broadcast(string message, int exclude); // 向所有活跃连接广播一条消息
    void sendMessage(int cid, string message);       // 向一个特定的tcp连接写入消息
private:
    TcpServer tcp_manager; 
    stack<int> free_indexs;   // 使用栈管理可用的下标
    set<int> active_indexs;   // 活跃的下标
    int connects[MAX_CONNECTED_CLIENT_NUM];   // socket_id 数组
    pthread_t tids[MAX_CONNECTED_CLIENT_NUM]; // tid数组
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
