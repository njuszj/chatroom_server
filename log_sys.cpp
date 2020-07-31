# include "log_sys.h"

Logger logger;   // 全局变量应该定义在这里而不是头文件

Logger::Logger(){
    // 默认构造函数
    this->target = terminal;
    this->level = debug;
    cout << "[WELCOME] " << __FILE__ << " " << currTime() << " : " << "=== Start logging ===" << endl;
}

Logger::Logger(log_target target, log_level level, string path){
        this->target = target;
        this->path = path;
        this->level = level;
        string tmp = "";  // 双引号下的常量不能直接相加，所以用一个string类型做转换
        string welcome_dialog = tmp + "[Welcome] " + __FILE__ + " " + currTime() + " : " + "=== Start logging ===\n";
        if (target != terminal){
            this->outfile.open(path, ios::out | ios::app);   // 打开输出文件
            this->outfile << welcome_dialog;
        }
        if (target != file){
            // 如果日志对象不是仅文件
            cout << welcome_dialog;
        }
    }

void Logger::output(string text, log_level act_level){
    int t = text.size();
    if(t == 0) return;
    else{
        // 进行预处理，删去多余的回车换行
        t-=1;
        while(t>=0 && (text[t] == '\n' || text[t] == '\r')) t--;
        text = text.substr(0, t+1);
    }
    string prefix;
    if(act_level == debug) prefix = "[DEBUG]   ";
    else if(act_level == info) prefix = "[INFO]    ";
    else if(act_level == warning) prefix = "[WARNING] ";
    else if(act_level == error) prefix = "[ERROR]   ";
    else prefix = "";
    prefix += __FILE__;
    prefix += " ";
    string output_content = prefix + currTime() + " : " + text + "\n";
    if(this->level <= act_level && this->target != file){
        // 当前等级设定的等级才会显示在终端，且不能是只文件模式
        cout << output_content;
    }
    if(this->target != terminal)
        outfile << output_content;
}


void Logger::DEBUG(string text){
    this->output(text, debug);
}

void Logger::INFO(string text){
    this->output(text, info);
}

void Logger::WARN(string text){
    this->output(text, warning);
}

void Logger::ERROR(string text){
    this->output(text, error);
}