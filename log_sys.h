// 日志记录

# ifndef LOG_SYS_H
# define LOG_SYS_H

# include "environment.h"
# include "utilities.h"

using std::ios;

class Logger{
public:
    enum log_level{debug, info, warning, error};// 日志等级
    enum log_target{file, terminal, file_and_terminal};// 日志输出目标
private:
    std::ofstream outfile;    // 将日志输出到文件的流对象
    log_target target;        // 日志输出目标
    string path;              // 日志文件路径
    log_level level;          // 日志
    void output(string text, log_level act_level);            // 输出行为
public:
    Logger();  // 默认构造函数
    Logger(log_target target, log_level level, string path);
    void DEBUG(string text);
    void INFO(string text);
    void WARN(string text);
    void ERROR(string text);
};

# endif