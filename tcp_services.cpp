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
}