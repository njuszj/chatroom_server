# include <iostream>
# include "utilities.h"
# include "log_sys.h"
# include "chatroom.h"
# include "db.h"

using namespace std;

void logger_test(){
    Logger logger(Logger::file_and_terminal, Logger::debug, "result.log");
    logger.DEBUG("What happend?");
    logger.INFO("This is good.");
    logger.WARN("Yes...");
    logger.ERROR("IO Error!");
}

void sql_test(){
    UserDBManager udb("chatroom.db");
}

void hash_test(){
    string hello = "sarfedfe";
    cout << std::tr1::hash<std::string>()(hello) << endl;
}

# ifdef SQL_TEST_ON
sql_test();
# endif

int main(){
  return 0;
}