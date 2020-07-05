# ifndef LOG_SYS_H
# define LOG_SYS_H

# include <iostream>
# include <fstream>
# include <string>
# include <time.h>
# include "utilities.h"

using std::string;
using std::cout;
using std::endl;
using std::ios;

enum log_level{debug, info, warning, error};// 日志等级
enum log_target{file, terminal, file_and_terminal};// 日志输出目标

class Logger{
private:
    std::ofstream outfile;    // 将日志输出到文件的流对象
    log_target target;        // 日志输出目标
    string path;              // 日志文件路径
    log_level level;          // 日志
    void output(string text, log_level act_level);            // 输出行为
public:
    Logger();  // 默认构造函数
    Logger(log_target target, string path, log_level level);
    void DEBUG(string text);
    void INFO(string text);
    void WARNING(string text);
    void ERROR(string text);
};

# endif