# include "db.h"

DBManager::DBManager(const char* filename){
    int r = sqlite3_open(filename, &db_ptr);
    if(r != SQLITE_OK) {
        logger.ERROR("打开sqlite3数据库失败");
        logger.ERROR(sqlite3_errmsg(db_ptr));
        exit(1);
    }
}

DBManager::~DBManager(){
    sqlite3_close(db_ptr);
}

string UserDBManager::hash(string password) const{
    return to_string(std::tr1::hash<std::string>()(password));
}

bool UserDBManager::verify(int account, string password) const{
    password = hash(password);
    const char sql[100] = "SELECT password from user where account"
}

int DBManager::execute(const char* sql){
    char *err_message = new char[100];
    int r = sqlite3_exec(db_ptr, sql, NULL, NULL, &err_message);
    if(r != SQLITE_OK){
        logger.ERROR("执行SQL语句出错!");
        logger.ERROR(err_message);
    }
    return r;
}

void ChatroomDBManager::createOriginTables(){
    // 建表语句
    execute("CREATE TABLE User( \
        id       INT PRIMARY KEY NOT NULL, \
        account  INT             NOT NULL, \
        nickname CHAR(100)       NOT NULL, \
        password CHAR(128)       NOT NULL);");
}
