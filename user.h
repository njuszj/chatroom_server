// 管理用户

# ifndef USER_H
# define USER_H
# include "environment.h"


class User{
private:
    int account;     // 帐号
    string nickname; // 昵称
    bool valid;      // 是否是有效用户
public:
    User():account(0), nickname(""){};
    ~User(){};
public:
    bool verify(int account, string password); // 验证密码是否正确
};

# endif