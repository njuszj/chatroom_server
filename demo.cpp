# include <iostream>
# include "utilities.h"
# include "log_sys.h"
# include "chatroom.h"
# include "db.h"

using namespace std;

void demo_test(){
    Chatroom ct;
    ct.startListen();
}

void logger_test(){
    Logger logger(Logger::file_and_terminal, Logger::debug, "result.log");
    logger.DEBUG("What happend?");
    logger.INFO("This is good.");
    logger.WARN("Yes...");
    logger.ERROR("IO Error!");
}

void sql_test(){
    UserDBManager udb("db_test.db");
    udb.cleanTable();
    udb.createTable();
    udb.insertUser(10001, "Alice", "123456");
    udb.insertUser(10002, "Bob", "19980723");
    udb.insertUser(10003, "Ciri", "admin123");
    string usr = udb.getUserName(10001);
    string passwd = udb.getPassword(10001);
    cout << "测试完毕" << endl;
    cout << usr << " : " << passwd << endl;
}

void hash_test(){
    string hello = "sarfedfe";
    cout << std::tr1::hash<std::string>()(hello) << endl;
}

int main(){
# ifdef SQL_TEST_ON
    sql_test();
# endif

# ifdef DEMO_TEST_ON
    demo_test();
# endif
}