# include "utilities.h"

string currTime(){
    // 获取当前时间，并规范表示
    char tmp[64];
    time_t ptime;
    time(&ptime);  // time_t time (time_t* timer);
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&ptime));
    return tmp;
}