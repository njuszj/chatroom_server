# include "user.h"

bool UserManager::verify(int account, string passwd){
    return db_manager.verify(account, passwd);
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

User::User(const User& rst){
    this->account = rst.account;
    this->username = rst.username;
    this->valid = rst.valid;
}

bool User::operator==(const User& rst){
    if(this->account == rst.account) return true;
    else return false;
}

bool User::operator!=(const User& rst){
    return !(*this == rst);
}

bool User::operator<(const User& rst) const{
    if(this->account < rst.account) return true;
    else return false;
}

void User::setUsername(string username){
    this->username = username;
}

string User::getUsername() const{
    return username;
}

int User::getAccount() const{
    return account;
}

void User::active(){
    this->valid = true;
}

void UserManager::setDatabase(const char* path){
    db_manager.changePtr(path);
}

void UserManager::addUser(int account, int cid){
    logger.INFO(string() + "用户: "+to_string(account)+"登录，连接id是: "+to_string(cid));
    User* user = new User(account);
    if(active_users.find(*user) != active_users.end()) {
        logger.INFO("用户已经登陆，无需重复登陆");
        delete user;
        return;
    }
    user->setUsername(db_manager.getUserName(account));
    user->active();
    active_users.insert(*user);
    cid_to_user[cid] = account;
    user_to_cid[account] = cid;
}

void UserManager::freeUser(const User& user){
    set<User>::iterator itor = active_users.find(user);
    if(itor != active_users.end()){
        // 释放User占用的资源， erase（应该?）会调用User的析构函数
        this->active_users.erase(user);
        user_to_cid.erase(user.getAccount());
    }
    logger.INFO("用户下线");
}

void UserManager::freeCid(int cid){
    cid_to_user.erase(cid);
}

int UserManager::getUserCid(int id){
    if(user_to_cid.find(id) != user_to_cid.end()){
        return user_to_cid[id];
    }
    else return 0;
}