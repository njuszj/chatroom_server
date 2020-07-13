# include "chatroom.h"

Chatroom::Chatroom(){
    // 默认构造函数
    socket_id = tcp_manager.createSocket();
    free_head->initByAutoInc(MAX_CONNECTED_CLIENT_NUM)
}

Chatroom::~Chatroom(){
}

void* Chatroom::process(int connect_id){

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

        }
    }
}