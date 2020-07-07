# include "tcp_services.h"


TcpServer::TcpServer(){
    // 构造函数, 初始化结构体
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = INADDR_ANY;  // 地址
    server_addr.sin_family = AF_INET;       // 协议族
    server_addr.sin_port = htons(PORT);    // 端口号
}


int TcpServer::createSocket(){
    // 创建一个socket连接，然后返回socket的标识符
    socket_id = socket(AF_INET, SOCK_STREAM, 0);  // 建立socket
    if(socket_id == -1){
        logger.ERROR("Failed to create TCP socket!");
        return -1;
    }
    int bind_r = bind(socket_id, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(bind_r == -1){
        logger.ERROR("Failed to bind address and port with the socket!");
        return -1;
    }
    return socket_id;
    /*
    char* buff = new char[4096];
    int n = recv(connect_id, buff, 4096, 0);
    buff[n] = '\n';
    std::cout << buff << std::endl;
    close(connect_id);
    close(socket_id);
    */
}


void TcpServer::startListen(void* (*func)(int)){
    // 开始监听端口, num: 最大监听数，　func: 处理函数
    // 每当接入一个新的连接，就将connect参数传递给处理函数，而自身继续监听
    int listen_r = listen(this->socket_id, MAX_LISTEN_NUM);
    if(listen_r == -1){
        // 日志记录
        return;
    }
    while(1){
        int connect_id = accept(socket_id, (struct sockaddr*)NULL, NULL);
        if(connect_id == -1){
            // 日志记录
            return;
        }
        func(connect_id);   // 转由处理函数处理
    }
}


