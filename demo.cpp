# include <iostream>
# include "utilities.h"
# include "log_sys.h"

using namespace std;

int main(){
    Logger logger;
    logger.DEBUG("What happend?");
    logger.INFO("This is good.");
    logger.WARNING("Yes...");
    logger.ERROR("IO Error!");
}