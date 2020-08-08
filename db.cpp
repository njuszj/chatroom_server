# include "db.h"

DBGetTable::~DBGetTable(){
    // 析构函数主要调用free_table函数释放资源
    sqlite3_free_table(res);
    sqlite3_free(err_msg);
}

char** DBGetTable::getTable(const char* sql){
    logger.INFO("进入SQL查询");
    char** _res = NULL;
    char* _err_msg = NULL;
    int _rows = 0;
    int _cols = 0;
    int r = sqlite3_get_table(db_ptr, sql, &_res, &_rows, &_cols, &_err_msg);
    if(r != SQLITE_OK){
        logger.ERROR(_err_msg);
    }
    logger.INFO(string()+"成功查询，行数"+to_string(rows)+"列数"+to_string(cols));
    return res;
}

string DBGetTable::getItem(const char* sql){
    // 只查询单个记录，返回字符串类型
    getTable(sql);
    if(cols > 1 || rows > 1){
        logger.WARN("返回字段不止一条");
    }
    else if(rows == 0){
        logger.WARN("没有查询到记录");
        return "sdcard";
    }
    logger.DEBUG(string()+"单个查询结果"+*(res+1));
    return *(res + 1);
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
    // 验证外部提供的密码是否正确
    char sql[100];
    sprintf(sql, "SELECT password from user where account='%d'", account);
    DBGetTable query_handle(db_ptr);
    string true_password = query_handle.getItem(sql);
    // 上面一条 BUG
    true_password = hash(true_password);
    password = hash(password);
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
    char sql[100];
    sprintf(sql, "SELECT username from user where account='%d'", account);
    DBGetTable query_handle(db_ptr);
    string username = query_handle.getItem(sql);
    return username;
}

void ChatroomDBManager::createOriginTables(){
    // 建表语句
    execute("CREATE TABLE User( \
        id       INT PRIMARY KEY NOT NULL  UNIQUE, \
        account  INT             NOT NULL  UNIQUE, \
        username CHAR(50)        NOT NULL  UNIQUE, \
        password CHAR(128)       NOT NULL, \
        birthday DATE, \
        email    CHAR(50), \
        remark   CHAR(100));");
}
