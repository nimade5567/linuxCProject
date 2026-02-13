#include<iostream>
#include<cstring>
#include<cerrno>
#include<ctime>
#include<fstream>

enum class LogLevel{
    INFO,
    WARN,
    ERROR,
    FATAL
};


#define LOG(level,msg) logError(level,__FILE__,__LINE__,msg)
#define LOG_INFO(msg) LOG(LogLevel::INFO,msg)
#define LOG_WARN(msg) LOG(LogLevel::WARN,msg)
#define LOG_ERROR(msg) LOG(LogLevel::ERROR,msg)




void logError(LogLevel level,const char* file,int line,const char* msg){
    static std::ofstream logFile("app.log", std::ios::app);

    time_t now=time(nullptr);
    std::tm tm_time;
    localtime_r(&now, &tm_time);
    char buffer[64];
    strftime(buffer, 
            sizeof(buffer),
            "%Y-%m-%d %H:%M:%S",
            &tm_time);
    const char* logStr;
    switch(level){
        case LogLevel::INFO:
            logStr="INFO";
            break;
        case LogLevel::WARN:
            logStr="WARN";
            break;
        case LogLevel::ERROR:
            logStr="ERROR";
            break;
        default:
            break;
    }
    if((std::string)logStr=="INFO"){
        logFile<<"data: "<<buffer<<" | "<<
    "level: "<<logStr<<" | "<<
    "file: "<<file<<" | "<<
    "line: "<<line<<" | "<<
    msg<<std::endl;
    }else{
        logFile<<"data: "<<buffer<<" | "<<
        "level: "<<logStr<<" | "<<
        "error code: "<<errno<<" | "<<
        "message: "<<strerror(errno)<<" | "<<
        "file: "<<file<<" | "<<
        "line: "<<line<<" | "<<
    msg<<std::endl;
    }
}
int main(){
     FILE* f = fopen("not_exist.txt", "r");
    if (!f)
    {

        LOG_WARN("Fopen Failed!");
    }
    return 0;
}