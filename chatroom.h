# ifndef CHATROOM_H
# define CHATROOM_H
# include "tcp_services.h"
# include "user.h"
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
    void sendMessageToUser(int , string); // 向一个注册的用户发送消息
    void cmdProcess(const char*, int);  // 命令处理模块
    void queryProcess(const char*, int); // 查询处理模块
    void setDatabase(const char* path);      // 设置数据库
private:
    void m_login(int cid);    // 用户登录
    void m_register(int cid); // 用户注册
    void m_query_status(int cid);  // 查询用户信息
    int m_getUserCid(int id); // 获取用户的TCP连接号
    TcpServer tcp_manager;
    UserManager user_manager; 
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