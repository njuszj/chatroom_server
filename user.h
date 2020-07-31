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
    User():account(0), username(""){};
    User(int ac, string nk):account(ac), username(nk){};
    ~User(){};
private:
    int account;     // 帐号
    string username; // 昵称
    bool valid;      // 是否是有效用户
public:
    User& operator=(const User&);
    bool operator==(const User&);
    bool operator<(const User&) const;
    bool isValid() const;
    string getNickname() const;
    int getAccount() const;
    void active();  // 激活用户
};

User verify(int account, string passwd); // 验证密码是否正确

# endif