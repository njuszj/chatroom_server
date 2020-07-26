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
    Chatroom();// 构造函数
    ~Chatroom();// 析构函数
    void startListen();//开始监听端口接受请求
    void freeIndexs(int index);  // 释放一个资源
    void freeUsers(const User&); // 一个用户离线
    void broadcast(string message, int exclude); // 向所有活跃连接广播一条消息
    void sendMessage(int cid, string message);       // 向一个特定的tcp连接写入消息
    void sendMessageToUser(int , string); // 向一个注册的用户发送消息
    void addUser(const User&, int);  // 添加一个活跃用户
    void cmdProcess(const char*, int);  // 命令处理
private:
    void m_login(int cid);  // 用户登录，返回一个用户对象
    int m_getUserCid(int id); // 获取用户的TCP连接号
    TcpServer tcp_manager;
    stack<int> free_indexs;  // 使用栈管理可用的下标
    set<int> active_indexs;  // 活跃的下标
    set<User> active_users;  // 在线用户
    map<int, int> cid_to_user; // 标记一个TCP连接是否是一个认证的用户, 一个TCP连接只有一个用户
    map<int, int> user_to_cid; // 一个用户对应的TCP连接，可能不止一个，但是暂时只取一个
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