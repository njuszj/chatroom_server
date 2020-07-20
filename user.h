// 管理用户

# ifndef USER_H
# define USER_H
# include "environment.h"
# include <map>
# include <vector>
# include <set>

using std::map;
using std::vector;
using std::set;

class User{
public:
    User():account(0), nickname(""){};
    ~User(){};
private:
    int account;     // 帐号
    string nickname; // 昵称
    bool valid;      // 是否是有效用户
public:
    set<int> connect_id_set;  // TCP连接集合
public:
    User& operator=(const User&);
    bool operator==(const User&);
    bool operator<(const User&) const;
    bool verify(int account, string passwd); // 验证密码是否正确
    bool isValid() const;
    string getNickname() const;
    int getAccount() const;
};

# endif