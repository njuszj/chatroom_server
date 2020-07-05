# include <iostream>
# include "utilities.h"
# include "log_sys.h"

using namespace std;

void logger_test(){
    Logger logger(Logger::file_and_terminal, Logger::debug, "./result.log");
    logger.DEBUG("What happend?");
    logger.INFO("This is good.");
    logger.WARNING("Yes...");
    logger.ERROR("IO Error!");
}

int main(){
    logger_test();
}