// 与数据库进行交互

# ifndef DB_H
# define DB_H

# include "environment.h"
# include "log_sys.h"
# include <tr1/functional>
# include <sqlite3.h>

extern Logger logger;

class DBGetTable{
private:
    sqlite3* db_ptr;
public:
    // 从面向对象设计角度来说应该是private的，但是这样sqlite无法访问这些成员(? 存疑)
    int cols;
    int rows;
    char** res;
    char* err_msg;
public:
    DBGetTable(sqlite3* ptr):cols(0), rows(0), res(NULL), err_msg(NULL){};
    DBGetTable() = delete;  // 不需要默认构造函数
    ~DBGetTable();
public:
    char** getTable(const char* sql);
    string getItem(const char* sql);
};

class DBManager{
public:
    DBManager():db_ptr(NULL){};
    DBManager(const char* filename);
    virtual ~DBManager();
    int execute(const char* sql);
protected:
    sqlite3* db_ptr; // 数据库文件指针
};

class ChatroomDBManager: public DBManager{
public:
    ChatroomDBManager():DBManager(){};
    ChatroomDBManager(const char* filename):DBManager(filename){};
    virtual ~ChatroomDBManager(){};
public:
    void createOriginTables();
};

class UserDBManager: public DBManager{
public:
    UserDBManager():DBManager(){};
    UserDBManager(const char* filename):DBManager(filename){};
    virtual ~UserDBManager(){};

    string hash(string password) const;     // 对密码进行哈希处理，避免明文储存
public:
    bool insertUser(int account, string username, string password);  // 新增用户
    bool modifyPassword(int account, string password); // 修改用户密码
    bool deleteUser(int account, string password);     // 删除用户
    bool verify(int account, string password) const; // 验证用户密码
    string getUserName(int account) const; // 获取用户名
};

# endif