# include "db.h"

DBGetTable::~DBGetTable(){
    // 析构函数主要调用free_table函数释放资源
    sqlite3_free_table(res);
    free(err_msg);
}

char** DBGetTable::get_table(const char* sql){
    int r = sqlite3_get_table(db_ptr, sql, &res, &rows, &cols, &err_msg);
    if(r != SQLITE_OK){
        logger.ERROR(err_msg);
    }
    return res;
}

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
    char sql[100];
    char **res = NULL;
    char *err_msg = NULL;
    int row,col,ret;
    sprintf(sql, "SELECT password from user where account='%s'", password.c_str());
    sqlite3_get_table(db_ptr, sql, &res, &row, &col, &err_msg);

    sqlite3_free_table(res);
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

void ChatroomDBManager::createOriginTables(){
    // 建表语句
    execute("CREATE TABLE User( \
        id       INT PRIMARY KEY NOT NULL, \
        account  INT             NOT NULL, \
        nickname CHAR(100)       NOT NULL, \
        password CHAR(128)       NOT NULL);");
}
