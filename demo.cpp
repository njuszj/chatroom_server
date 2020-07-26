# include <iostream>
# include "utilities.h"
# include "log_sys.h"
# include "chatroom.h"
# include "db.h"

# include <tr1/functional>

using namespace std;

// void logger_test(){
//     Logger logger(Logger::file_and_terminal, Logger::debug, "result.log");
//     logger.DEBUG("What happend?");
//     logger.INFO("This is good.");
//     logger.WARNING("Yes...");
//     logger.ERROR("IO Error!");
// }

// void sql_test(){
//     ChatroomDBManager cdb("chatroom.db");
//     cdb.createOriginTables();
// }

void hash_test(){
    string hello = "sarfedfe";
    cout << std::tr1::hash<std::string>()(hello) << endl;
}

int main(){
    // Chatroom se;
    // se.startListen();
    // sql_test();
    hash_test();
}