# ifndef CHATROOM_H
# define CHATROOM_H
# include "tcp_services.h"
# include "user.h"
# include "environment.h"

# define MAX_CONNECTED_CLIENT_NUM 100
# define RECV_BUFFSIZE 4096
# define SHORT_BUFFSIZE 128

extern Logger logger;

class Chatroom{
    // 聊天室服务端主体
public:
    Chatroom();// 构造函数
    ~Chatroom();// 析构函数
    void startListen();//开始监听端口接受请求
    void freeIndexs(int index);  // 释放一个资源
    void freeUsers(const User&); // 一个用户离线
    void broadcast(const char*); // 向所有活跃连接广播一条消息
    void sendMessage(int cid, const char* message);       // 向一个特定的tcp连接写入消息
    void addUser(const User&);  // 添加一个活跃用户
    User login(int cid);  // 用户登录，返回一个用户对象
private:
    TcpServer tcp_manager;
    stack<int> free_indexs;  // 使用栈管理可用的下标
    set<int> active_indexs;  // 活跃的下标
    set<User> active_users;  // 在线用户
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