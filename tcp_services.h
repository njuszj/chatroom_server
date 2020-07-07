# ifndef TCP_SERVICES_H
# define TCP_SERVICES_H

# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <memory.h>
# include <string.h>
# include <sys/socket.h>
# include<netinet/in.h>
# include <unistd.h>
# include "log_sys.h"

# define PORT 9999
# define MAX_LISTEN_NUM 20

class TcpServer{
    // 管理TCP服务端的连接
private:
    Logger logger;
    int socket_id;  // socket 标识符, 由本机IP地址和端口号唯一确定，所以是唯一的
    // int connect_id; // connect 标识符，由服务端和客户端两组(IP, Port)确定，所以可以有很多个
    struct sockaddr_in server_addr;  // 表征服务端信息的结构体
public:
    TcpServer();
    int createSocket();
    void startListen(void* (*func)(int));
    
};

# endif