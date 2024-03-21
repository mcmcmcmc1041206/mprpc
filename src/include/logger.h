#pragma once
#include "lockqueue.h"
#include <string>

enum LogLevel
{
    INFO,//普通的日志信息
    ERROR,//错误信息
};

//Mprpc框架提供的日志系统
class Logger
{
public:
    //获取日志的单例
    static Logger& GetInstance();
    //设置日志级别
    void SetLogLevel(LogLevel level);
    //写日志
    void log(std::string msg);
private:
    int m_loglevel;//记录日志级别
    LockQueue<std::string> m_lckQue;//日志缓冲队列

    Logger();
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
};

//定义宏 LOG_INFO("xxx %d %s")
#define LOG_INFO(logmsgformat, ...)\
    do\
    {\
        Logger &logger = Logger::GetInstance();\
        logger.SetLogLevel(INFO);\
        char c[1024] = {0};\
        snprintf(c,1024,logmsgformat,##__VA_ARGS__);\
        logger.log(c);\
    }while(0);

#define LOG_ERR(logmsgformat, ...)\
    do\
    {\
        Logger &logger = Logger::GetInstance();\
        logger.SetLogLevel(ERROR);\
        char c[1024] = {0};\
        snprintf(c,1024,logmsgformat,##__VA_ARGS__);\
        logger.log(c);\
    }while(0);