#include "log.h"

#include<iostream>
#include<cstring>
#include<cerrno>
#include<ctime>
#include<fstream>








void mylog::logError(LogLevel level,const char* file,int line,const char* msg){
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