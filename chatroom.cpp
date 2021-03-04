# include "chatroom.h"

ProcessArg::ProcessArg(int cid, int index, Chatroom* ct){
    this->ct = ct;
    this->index = index;
    this->cid = cid;
}

Chatroom::Chatroom(){
    // 默认构造函数
    socket_id = tcp_manager.createSocket();
    for(int i=99; i>=0; i--){
        // 初始化空闲栈
        free_indexs.push(i);
    }
}

Chatroom::~Chatroom(){

}

void* process(void* arg){
    // 处理函数，负责接收每一个客户发来的消息
    pthread_detach(pthread_self());       // 防止线程阻塞
    ProcessArg* parg = (ProcessArg*)arg;  // 传入参数
    Chatroom* server = parg->ct;
    int cid = parg->cid;  // connect socket id
    char* buff = new char[RECV_BUFFSIZE];     // 创建接收缓冲区
    string tmpinfo = string() + "新的线程启动, 编号: " + to_string(pthread_self()) + ", socket id: " + to_string(cid);
    logger.INFO(tmpinfo);
    while(1){
        // 循环接受消息，并处理消息
        memset(buff, 0, RECV_BUFFSIZE);
        int n = recv(cid, buff, RECV_BUFFSIZE, 0);  // buff会自动添加一个\0结束标志
        logger.INFO(string() + "收到消息: " + buff);
        if(n > 0) server->broadcast(buff, cid);
        else break;
    }
    close(cid);
    logger.INFO(string() + "线程 " + to_string(pthread_self()) + " 已结束");
    pthread_exit(NULL);
    return NULL;
}

void Chatroom::startListen(){
    // 每当接入一个新的连接，就将connect参数传递给处理函数，而自身继续监听
    int listen_r = listen(this->socket_id, MAX_LISTEN_NUM);
    if(listen_r == -1){
        logger.ERROR("Failed to listen port! ");
        return;
    }
    while(1){
        // 循环接收一个新的TCP连接，建立新的线程处理连接
        int connect_id = accept(socket_id, (struct sockaddr*)NULL, NULL);
        if(connect_id == -1){
            logger.ERROR("Failed to accept connect request! ");
            return;
        }
        else {
            if(free_indexs.empty()) {
                logger.ERROR("连接已达上限!");
                close(connect_id);
            }
            int index = free_indexs.top(); // 取一个下标
            free_indexs.pop();
            connects[index] = connect_id;
            ProcessArg arg(connect_id, index, this);  // 构造传入的参数
            active_indexs.insert(index);
            int rt = pthread_create(&tids[index], NULL, process, (void*)&arg);  // 创建新的线程处理连接
            if(rt)
                logger.ERROR("Failed to create a new thread! ");
        }
    }
}

void Chatroom::broadcast(string message, int exclude){
    // 向所有TCP连接广播一条消息，除了exclude
    set<int>::iterator itor = active_indexs.begin();
    logger.INFO(string()+"开始向所有在线用户广播一条消息: "+message);
    for(; itor != active_indexs.end(); itor++){
        int cid = connects[*itor];
        if(cid != exclude)
            sendMessage(cid, message);
    }
}

void Chatroom::sendMessage(int cid, string message){
    // 向一个TCP连接发送一条消息
    if(cid<=0) return;
    int r = send(cid, message.data(), message.size(), 0);
    if(r>=0)
       logger.INFO(string()+"向 "+to_string(cid)+" 发了一条消息: "+message);
    else
        logger.ERROR("发送错误!");
}

void Chatroom::freeIndexs(int index){
    // 释放一个index
    connects[index] = 0;
    tids[index] = 0;
    if(active_indexs.find(index) != active_indexs.end())
        active_indexs.erase(index);  // 从活跃集合中移除
    free_indexs.push(index);  // 放回可用栈中
}