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
    logger.WARNING("Yes...");
    logger.ERROR("IO Error!");
}

void sql_test(){
    ChatroomDBManager cdb("chatroom.db");
    cdb.createOriginTables();
}

int main(){
    // Chatroom se;
    // se.startListen();
    sql_test();
}