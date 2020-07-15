# include "chatroom.h"

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

/*
    close(connect_id);
    close(socket_id);
*/

void* process(void* arg){
    pthread_detach(pthread_self());  // 防止线程阻塞
    int cid = *((int*)arg);
    char* buff = new char[RECV_BUFFSIZE];     // 创建接收缓冲区
    string tmpinfo = string() + "新的线程启动, 编号: " + to_string(pthread_self()) + ", socket id: " + to_string(cid);
    logger.INFO(tmpinfo);

    while(1){
        memset(buff, 0, RECV_BUFFSIZE);
        int n = recv(cid, buff, 4096, 0);
        if(n>=1 && buff[n-1] != '\n')
            buff[n] = '\n';  // 添加一个换行
        logger.INFO(string() + "收到消息: " + buff);
    }
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
            int index = s_indexs.top(); // 取一个下标
            s_indexs.pop();
            connects[index] = connect_id;
            int rt = pthread_create(&tids[index], NULL, process, (void*)(&connects[index]));  // 创建新的线程处理连接
            if(rt)
                logger.ERROR("Failed to create a new thread! ");
        }
    }
}