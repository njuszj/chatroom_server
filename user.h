// 管理用户

# ifndef USER_H
# define USER_H
# include "environment.h"
# include "db.h"
# include <map>
# include <vector>
# include <set>

extern Logger logger;

using std::map;
using std::vector;
using std::set;

class User{
    // 这个类储存一个用户的信息
public:
    User():account(0), username(""){};
    User(const User&);
    User(int ac):account(ac){};
    ~User(){};
private:
    int account;     // 帐号
    string username; // 昵称
    bool valid;      // 是否是有效用户
public:
    User& operator=(const User&);
    bool operator==(const User&);
    bool operator!=(const User&);
    bool operator<(const User&) const;
    bool isValid() const;
    string getUsername() const;
    void setUsername(string username);
    int getAccount() const;
    void active();  // 激活用户
};

class UserManager{
public:
    bool verify(int account, string passwd);   // 验证密码是否正确
    void addUser(int, int);            // 添加一个活跃用户
    void freeUser(const User&);               // 一个用户离线
    void freeCid(int cid);                    // 一个tcp连接断开，对应的用户释放
    int getUserCid(int id);
    void setDatabase(const char* path);
    UserDBManager db_manager;
private:
    set<User> active_users;    // 在线用户
    map<int, int> cid_to_user; // 标记一个TCP连接是否是一个认证的用户, 一个TCP连接只有一个用户
    map<int, int> user_to_cid; // 一个用户对应的TCP连接，可能不止一个，但是暂时只取一个
};


# endif