# ifndef CHATROOM_H
# define CHATROOM_H
# include "tcp_services.h"
# include <pthread.h>

# define MAX_CONNECTED_CLIENT_NUM 100

class freeListNode{
    //　空闲链表节点 
public:
    int val;
    freeListNode* next;
public:
    freeListNode(){
        val = 0;
        next = NULL;
    }
    freeListNode(int val){
        this->val = val;
        next = NULL;
    }
};

class freeList{
    // 空闲链表
public:
    freeListNode* head;
public:
    void initByAutoInc(int num){
        // 建立从0到num的递增序号链表
        freeListNode* curr = head;
        for(int i=0; i<num; i++){
            freeListNode* node = new freeListNode(i);
            curr->next = node;
            curr = node;
        }
    }
};

class Chatroom{
    // 聊天室服务端主体
public:
    Chatroom();// 构造函数
    ~Chatroom();// 析构函数
private:
    TcpServer tcp_manager;
    Logger logger;
    freeList* free_head;
    int connects[MAX_CONNECTED_CLIENT_NUM];
    int socket_id;
    void* process(int connect_id);//处理函数
    void startListen();//开始监听端口接受请求
};

# endif