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