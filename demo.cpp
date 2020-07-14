# include <iostream>
# include "utilities.h"
# include "log_sys.h"
# include "chatroom.h"

using namespace std;

void logger_test(){
    logger.DEBUG("What happend?");
    logger.INFO("This is good.");
    logger.WARNING("Yes...");
    logger.ERROR("IO Error!");
}

int main(){
    Chatroom se;
    se.startListen();
}