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
        s_indexs.push(i);
    }
}

Chatroom::~Chatroom(){

}


void* process(void* arg){
    pthread_detach(pthread_self());  // 防止线程阻塞
    ProcessArg* parg = (ProcessArg*)arg;
    int cid = parg->cid;
    char* buff = new char[RECV_BUFFSIZE];     // 创建接收缓冲区
    string tmpinfo = string() + "新的线程启动, 编号: " + to_string(pthread_self()) + ", socket id: " + to_string(cid);
    logger.INFO(tmpinfo);

    while(1){
        memset(buff, 0, RECV_BUFFSIZE);
        int n = recv(cid, buff, 4096, 0);  // buff会自动添加一个\0结束标志
        logger.INFO(string() + "收到消息: " + buff);
        if(strcmp(buff, "Bye\n") == 0) break;
        for(int i=0; i<n; i++) cout << i << " " << buff[i] << " ";
        cout << endl;
    }
    close(cid);
    parg->ct->freeIndexs(parg->index);
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
        int connect_id = accept(socket_id, (struct sockaddr*)NULL, NULL);
        if(connect_id == -1){
            logger.ERROR("Failed to accept connect request! ");
            return;
        }
        else {
            if(s_indexs.empty()) {
                logger.ERROR("连接已达上限!");
                close(connect_id);
            }
            int index = s_indexs.top(); // 取一个下标
            s_indexs.pop();
            connects[index] = connect_id;
            ProcessArg arg(connect_id, index, this);  // 构造传入的参数
            int rt = pthread_create(&tids[index], NULL, process, (void*)&arg);  // 创建新的线程处理连接
            if(rt)
                logger.ERROR("Failed to create a new thread! ");
        }
    }
}

void Chatroom::freeIndexs(int index){
    // 释放一个index
    connects[index] = 0;
    tids[index] = 0;
    s_indexs.push(index);  // 放回可用栈中
}