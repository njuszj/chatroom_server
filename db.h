// 与数据库进行交互

# ifndef DB_H
# define DB_H

# include "environment.h"
# include "log_sys.h"
# include <tr1/functional>
# include <sqlite3.h>
# include <assert.h>


extern Logger logger;

class DBManager{
public:
    DBManager():db_ptr(NULL){};
    DBManager(const char* filename);
    virtual ~DBManager();
    int execute(const char* sql);
    virtual void createTable();
    virtual void cleanTable();
    void changePtr(const char* path);
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
    // 管理数据库中的用户表
public:
    // 向回调函数传递的数据结构
    struct S_hash_password {
        string hash_password;
    };
    struct S_username {
        string username;
    };
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
    int getMinUseableAccount() const;                      // 获取最小可用账号(用于注册)
    string getUserName(int account) const;        // 获取用户名
    string getPassword(int account) const;        // 获取密码
private:
    static int callback_getUsername(void* para, int colnums, char** data, char** cols);
    static int callback_getPassword(void* para, int colnums, char** data, char** cols);
    static int callback_getMinUseableAccount(void* para, int colnums, char** data, char** cols);
};
# endif