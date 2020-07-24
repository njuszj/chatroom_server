// 与数据库进行交互

# ifndef DB_H
# define DB_H

# include "environment.h"
# include "log_sys.h"
# include <sqlite3.h>

class DBManager{
public:
    DBManager():db_ptr(NULL){};
    DBManager(const char* filename);
    ~DBManager();

    int execute(const char* sql);
protected:
    Logger logger;  // 日志记录
private:
    sqlite3* db_ptr; // 数据库文件指针
};

class ChatroomDBManager: public DBManager{
    
};

# endif