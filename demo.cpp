# include <iostream>
# include "utilities.h"
# include "log_sys.h"
# include "chatroom.h"

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

int main(){
# ifdef DEMO_TEST_ON
    demo_test();
# endif
}