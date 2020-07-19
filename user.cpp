# include "user.h"

bool User::verify(int account, string passwd){
    this->account = account;
    this->nickname = "Mr.Rand";
    this->valid = true;
    return true;
}

bool User::isValid(){
    return valid;
}

User& User::operator=(const User& rst){
    this->account = rst.account;
    this->nickname = rst.nickname;
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

string User::getNickname(){
    return nickname;
}