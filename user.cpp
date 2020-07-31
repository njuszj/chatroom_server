# include "user.h"

User verify(int account, string passwd){
    User user(account, "Mr.rand");
    user.active();
    return user;
}

bool User::isValid() const{
    return valid;
}

User& User::operator=(const User& rst){
    this->account = rst.account;
    this->username = rst.username;
    this->valid = rst.valid;
    return *this;
}

bool User::operator==(const User& rst){
    if(this->account == rst.account) return true;
    else return false;
}

bool User::operator<(const User& rst) const{
    if(this->account < rst.account) return true;
    else return false;
}

string User::getNickname() const{
    return username;
}

int User::getAccount() const{
    return account;
}

void User::active(){
    this->valid = true;
}