# include "db.h"

int UserDBManager::callback(void* para, int colnums, char** data, char** cols){
    // 对每一条查询结果调用一次该回调函数
    for(int i=0; i<colnums; i++){
        cout << cols[i] << " |";
    }
    cout << endl;
    for(int i=0; i<colnums; i++){
        cout << data[i] << " |";
    }
    cout << endl;
    return 0;
}

int UserDBManager::callback_getPassword(void* para, int colnums, char** data, char** cols){
    // 对每一条查询结果调用一次该回调函数
    char* password = (char*)(para);
    assert(colnums == 1);  // 应该假定只有一列结果
    strncpy(password, data[0], strlen(data[0]));
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
    // DBGetTable query_handle(db_ptr);
    string username;
    int r = sqlite3_exec(db_ptr, sql, callback, NULL, NULL);
    return username;
}

string UserDBManager::getPassword(int account) const{
    // 返回对应用户(哈希过后的)密码
    char sql[128];
    sprintf(sql, "SELECT password from user where account='%d'", account);
    string password;
    char* errmsg; // 错误信息
    int r = sqlite3_exec(db_ptr, sql, callback_getPassword, (void*)(&password), &errmsg);
    password = hash(password);
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