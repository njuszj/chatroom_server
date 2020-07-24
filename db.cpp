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

int DBManager::execute(const char* sql){
    int r = sqlite3_exec(db_ptr, sql, NULL, NULL, NULL);
    return r;
}
