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

void Chatroom::setDatabase(const char* path){
    user_manager.setDatabase(path);
}

void Chatroom::cmdProcess(const char* buff, int cid){
    // 命令处理模块
    if(strncmp(buff, "cmd@login", 9) == 0){
        // 进入用户登录模块
        m_login(cid);
    }
    else if(strncmp(buff, "cmd@register", 12) == 0){
        // 进入用户注册模块
    }
    else return;
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
        if(strncmp(buff, "cmd@", 4) == 0){
            if(strncmp(buff, "cmd@bye", 7) == 0) break;
            // 进入命令处理模块
            else server->cmdProcess(buff, cid);
        }
        else if(n > 0) server->broadcast(buff, cid);
        else break;
    }
    close(cid);
    server->freeIndexs(parg->index);
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

void Chatroom::m_login(int cid){
    // 用户尝试登录
    // 接收帐号信息
    User *user = NULL;
    char account[SHORT_BUFFSIZE];     // 为帐号创建接收缓冲区
    char passwd[SHORT_BUFFSIZE];
    sendMessage(cid, "ACCOUNT: ");
    memset(account, 0, SHORT_BUFFSIZE);
    int r1 = recv(cid, account, SHORT_BUFFSIZE, 0);
    if(r1>=0)
        logger.INFO(string() + "登录中，收到帐号: " + account);
    else{
        logger.INFO("用户帐号接收错误");
    }
    sendMessage(cid, "PASSWORD: ");
    memset(passwd, 0, SHORT_BUFFSIZE);
    int r2 = recv(cid, passwd, SHORT_BUFFSIZE, 0);
    if(r2>=0)
        logger.INFO(string()+"收到用户发来的密码");
    else{
        logger.INFO("用户密码接收错误");
    }

    int digital_account = atoi(account);
    user = user_manager.verify(digital_account, passwd);
    if(user){
        logger.INFO(string()+"用户成功登录");
        sendMessage(cid, "Welcome to chatroom!");
        this->user_manager.addUser(*user, cid);
        return;
    }
    else{
        sendMessage(cid, "ERROR LOGIN");
        logger.INFO(string()+"用户登录失败");
        delete user;  // 释放资源
        return;
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
    user_manager.freeCid(connects[index]);
    connects[index] = 0;
    tids[index] = 0;
    if(active_indexs.find(index) != active_indexs.end())
        active_indexs.erase(index);  // 从活跃集合中移除
    free_indexs.push(index);  // 放回可用栈中
}

void Chatroom::sendMessageToUser(int id, string message){
    int cid = m_getUserCid(id);
    sendMessage(cid, message);
}

int Chatroom::m_getUserCid(int id){
    return user_manager.getUserCid(id);
}