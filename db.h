// 与数据库进行交互

# ifndef DB_H
# define DB_H

# include "environment.h"
# include "log_sys.h"
# include <tr1/functional>
# include <sqlite3.h>

extern Logger logger;

class DBManager{
public:
    DBManager():db_ptr(NULL){};
    DBManager(const char* filename);
    virtual ~DBManager();
    int execute(const char* sql);
    virtual void createTable();
    virtual void cleanTable();
protected:
    sqlite3* db_ptr; // 数据库文件指针
};

class ChatroomDBManager: public DBManager{
public:
    ChatroomDBManager():DBManager(){};
    ChatroomDBManager(const char* filename):DBManager(filename){};
    virtual ~ChatroomDBManager(){};
};


class UserDBManager: public DBManager{
private:
    string hash(string password) const;     // 对密码进行哈希处理，避免明文储存
public:
    UserDBManager():DBManager(){};
    UserDBManager(const char* filename):DBManager(filename){};
    virtual ~UserDBManager(){};
    virtual void createTable();
    virtual void cleanTable();
    bool insertUser(int account, string username, string password);  // 新增用户
    bool modifyPassword(int account, string password); // 修改用户密码
    bool deleteUser(int account, string password);     // 删除用户
    bool verify(int account, string password) const; // 验证用户密码
    string getUserName(int account) const; // 获取用户名
private:
    static int callback(void* para, int colnums, char** data, char** cols);
};
# endif