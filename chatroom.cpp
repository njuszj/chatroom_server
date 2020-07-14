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

void* process(void* arg){
    pthread_detach(pthread_self());  // 防止线程阻塞
    string tmpinfo = "新的线程启动, 编号: ";
    tmpinfo += to_string(pthread_self());
    logger.INFO(tmpinfo);
    while(1){
        sleep(1);
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
            connects[index] = connect_id;
            int rt = pthread_create(&tids[index], NULL, process, NULL);  // 创建新的线程处理连接
            if(rt)
                logger.ERROR("Failed to create a new thread! ");
        }
    }
}