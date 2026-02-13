#ifndef LOG_H
#define LOG_H

enum class LogLevel{
    INFO,
    WARN,
    ERROR,
    FATAL
};

#define LOG(level,msg) mylog::logError(level,__FILE__,__LINE__,msg)
#define LOG_INFO(msg) LOG(LogLevel::INFO,msg)
#define LOG_WARN(msg) LOG(LogLevel::WARN,msg)
#define LOG_ERROR(msg) LOG(LogLevel::ERROR,msg)

namespace mylog{
    void logError(LogLevel level,const char* file,int line,const char* msg);
}

#endif