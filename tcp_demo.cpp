# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <memory.h>
# include <string.h>
# include <sys/socket.h>
# include<netinet/in.h>
# include <unistd.h>

# define PORT 9999

class ServerDemo{
private:
    int socket_id;  // socket 标识符
    int connect_id; // connect 标识符
    struct sockaddr_in server_addr;  // 表征服务端信息的结构体
public:
    ServerDemo(){
        // 构造函数, 初始化结构体
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_addr.s_addr = INADDR_ANY;  // 地址
        server_addr.sin_family = AF_INET;       // 协议族
        server_addr.sin_port = htons(PORT);    // 端口号
    }
    void create_socket(){
        socket_id = socket(AF_INET, SOCK_STREAM, 0);  // 建立socket
        if(socket_id == -1){
            // 日志记录
            std::cout << "1" << std::endl;
            return;
        }
        int bind_r = bind(socket_id, (struct sockaddr*)&server_addr, sizeof(server_addr));
        if(bind_r == -1){
            // 日志记录
            std::cout << "2" << std::endl;
            return;
        }
        int listen_r = listen(socket_id, 100);
        if(listen_r == -1){
            // 日志记录
            return;
        }
        connect_id = accept(socket_id, (struct sockaddr*)NULL, NULL);
        if(connect_id == -1){
            // 日志记录
            std::cout << connect_id << std::endl;
            return;
        }
        char* buff = new char[4096];
        int n = recv(connect_id, buff, 4096, 0);
        buff[n] = '\n';
        std::cout << buff << std::endl;
        close(connect_id);
        close(socket_id);
    }
};

int main(){
    ServerDemo s;
    s.create_socket();
}