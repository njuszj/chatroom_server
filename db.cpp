# include "db.h"

void UserDBManager::createTable(){
    // 创建用户表
    execute("CREATE TABLE User( \
        id       INTEGER PRIMARY KEY NOT NULL UNIQUE, \
        account  INT             NOT NULL  UNIQUE, \
        username CHAR(50)        NOT NULL  UNIQUE, \
        password CHAR(128)       NOT NULL, \
        birthday DATE, \
        email    CHAR(50), \
        remark   CHAR(100));");
}

int UserDBManager::callback_getUsername(void* para, int colnums, char** data, char** cols){
    // 对每一条查询结果调用一次该回调函数
    S_username* un = (S_username*)(para);
    assert(colnums == 1);
    un->username = data[0];
    return 0;
}

int UserDBManager::callback_getPassword(void* para, int colnums, char** data, char** cols){
    // 对每一条查询结果调用一次该回调函数
    S_hash_password* hp = (S_hash_password*)(para);
    assert(colnums == 1);  // 应该假定只有一列结果
    hp->hash_password = data[0];
    return 0;
}

int UserDBManager::callback_getMinUseableAccount(void* para, int colnums, char** data, char** cols){
    assert(colnums == 1);  // 应该假定只有一列结果
    int* account = (int*)(para);
    *account = atoi(data[0]);
    return 0;
}


DBManager::DBManager(const char* filename){
    int r = sqlite3_open(filename, &db_ptr);
    if(r != SQLITE_OK) {
        logger.ERROR("打开sqlite3数据库失败");
        logger.ERROR(sqlite3_errmsg(db_ptr));
        exit(1);
    }
}

void DBManager::createTable(){
    return;
}

void DBManager::cleanTable(){
    return;
}

DBManager::~DBManager(){
    sqlite3_close(db_ptr);
}

string UserDBManager::hash(string password) const{
    int n = password.size() - 1;
    while(n >= 0 && (password[n] == '\r' || password[n] == '\n'))
        password[n--] = '\0';
    return to_string(std::tr1::hash<std::string>()(password.c_str()));
}

bool UserDBManager::verify(int account, string password) const{
    // 验证外部提供的密码是否正确
    logger.DEBUG("进入底层密码验证函数");
    logger.DEBUG(string() + "收到密码" + password);
    password = hash(password);
    logger.DEBUG(string() + "收到哈希密码" + password);
    string true_password = getPassword(account);
    logger.DEBUG(string() + "真实密码" + true_password);
    if(true_password == password) return true;
    else return false;
}

int DBManager::execute(const char* sql){
    char *err_message = NULL;
    int r = sqlite3_exec(db_ptr, sql, NULL, NULL, &err_message);
    if(r != SQLITE_OK){
        logger.ERROR("执行SQL语句出错!");
        logger.ERROR(err_message);
    }
    return r;
}

string UserDBManager::getUserName(int account) const{
    char sql[128];
    sprintf(sql, "SELECT username from user where account='%d'", account);
    S_username* struct_username = new S_username();
    char* errmsg;
    int r = sqlite3_exec(db_ptr, sql, callback_getUsername, (void*)(struct_username), &errmsg);
    string username = struct_username->username;
    delete struct_username;
    return username;
}

string UserDBManager::getPassword(int account) const{
    // 返回对应用户(哈希过后的)密码
    char sql[128];
    sprintf(sql, "SELECT password from user where account='%d'", account);
    S_hash_password* struct_password = new S_hash_password();
    char* errmsg; // 错误信息
    int r = sqlite3_exec(db_ptr, sql, callback_getPassword, (void*)(struct_password), &errmsg);
    string password = struct_password->hash_password;
    delete struct_password;
    return password;
}

int UserDBManager::getMinUseableAccount() const{
    char sql[128] = "SELECT max(account) from user;";
    int account = 0;
    char* errmsg;
    int r = sqlite3_exec(db_ptr, sql, callback_getMinUseableAccount, (void*)(&account), &errmsg);
    account++;
    return account;
}

bool UserDBManager::insertUser(int account, string username, string password){
    char sql[128] = "";
    password = hash(password);
    sprintf(sql, "INSERT INTO User (account, username, password) VALUES(%d, '%s', '%s');", account, username.c_str(), password.c_str());
    return execute(sql);
}

void UserDBManager::cleanTable(){
#ifndef SQL_TEST_ON
    return;
#endif
    execute("DROP TABLE IF EXISTS User;");
}

void DBManager::changePtr(const char* path){
    int r = sqlite3_open(path, &db_ptr);
    if(r != SQLITE_OK) {
        logger.ERROR("打开sqlite3数据库失败");
        logger.ERROR(sqlite3_errmsg(db_ptr));
        exit(1);
    }
}