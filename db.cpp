# include "db.h"


int UserDBManager::callback_getUsername(void* para, int colnums, char** data, char** cols){
    // 对每一条查询结果调用一次该回调函数
    s_username* un = (s_username*)(para);
    assert(colnums == 1);
    un->username = data[0];
    return 0;
}

int UserDBManager::callback_getPassword(void* para, int colnums, char** data, char** cols){
    // 对每一条查询结果调用一次该回调函数
    user_hash_password* hp = (user_hash_password*)(para);
    assert(colnums == 1);  // 应该假定只有一列结果
    hp->hash_password = data[0];
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
    return to_string(std::tr1::hash<std::string>()(password));
}

bool UserDBManager::verify(int account, string password) const{
    // 验证外部提供的密码是否正确
    password = hash(password);
    string true_password = getPassword(account);
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
    s_username* struct_username = new s_username();
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
    user_hash_password* struct_password = new user_hash_password();
    char* errmsg; // 错误信息
    int r = sqlite3_exec(db_ptr, sql, callback_getPassword, (void*)(struct_password), &errmsg);
    string password = hash(struct_password->hash_password);
    delete struct_password;
    return password;
}

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