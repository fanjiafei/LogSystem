#include "logSystem.h"
#include <syslog.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
LogSystem* logHandler = NULL;

LogSystem::LogSystem()
{
}

LogSystem::~LogSystem()
{
}

void LogSystem::LogInfo(const char *stringFormat, ...) throw()
{
}

void LogSystem::LogDebug(const char *stringFormat, ...) throw()
{
}

void LogSystem::LogWarning(const char *stringFormat, ...) throw()
{
}

void LogSystem::LogError(const char *stringFormat, ...) throw()
{
}

void LogSystem::setLogPri(uint8_t pri)
{
}

LogSystem* LogSystem::getInstance(){
    char *logMode;
    char sysMode[]="syslog";

    if(NULL==logHandler){
        logMode = getenv("LOGMODE");
        if(NULL==logMode||strcmp(sysMode,logMode)!=0){
            printf("log to tty\n");
            logHandler = new LogTotty();
        }else{
            printf("log to syslog\n");
            logHandler = new LogTosyslog();
        }
    }
    return logHandler;
}

LogTotty::LogTotty()
{
    priority = atoi( NULL == getenv( "LOGLEVEL" ) ? "3" : getenv( "LOGLEVEL" ) );
    logMsg[1024]={0};
}

void LogTotty::LogInfo(const char *stringFormat, ...) throw()
{

    if (priority >= LOG_INFO)
    {
        va_list va;
        va_start(va,stringFormat);
        clock_gettime(CLOCK_MONOTONIC, &ts);
        vsprintf(logMsg, stringFormat, va);
        std::cout <<GREEN<< "[IPC_Serial][INFO]:" <<'['<<ts.tv_sec <<'.'<<ts.tv_nsec<<']'<< logMsg<< std::endl;
        va_end(va);
    }
}

void LogTotty::LogDebug(const char *stringFormat, ...) throw()
{
    if (priority >= LOG_DEBUG)
    {
        va_list va;
        va_start(va,stringFormat);
        clock_gettime(CLOCK_MONOTONIC, &ts);
        vsprintf(logMsg, stringFormat, va);
        std::cout <<GREEN << "[IPC_Serial][DEBUG]:" <<'['<<ts.tv_sec <<'.'<<ts.tv_nsec<<']'<<logMsg << std::endl;
        va_end(va);
    }
}

void LogTotty::LogWarning(const char *stringFormat, ...) throw()
{
    if (priority >= LOG_WARNING)
    {
        va_list va;
        va_start(va,stringFormat);
        clock_gettime(CLOCK_MONOTONIC, &ts);
        vsprintf(logMsg, stringFormat, va);
        std::cout <<YELLOW<< "[IPC_Serial][WARN]:" <<'['<<ts.tv_sec <<'.'<<ts.tv_nsec<<']'<<logMsg << std::endl;
        va_end(va);
    }
}

void LogTotty::LogError(const char *stringFormat, ...) throw()
{
    if (priority >= LOG_ERR)
    {
        va_list va;
        va_start(va,stringFormat);
        clock_gettime(CLOCK_MONOTONIC, &ts);
        vsprintf(logMsg, stringFormat, va);
        std::cout <<RED<< "[IPC_Serial][ERROR]:" <<'['<<ts.tv_sec <<'.'<<ts.tv_nsec<<']'<<logMsg << std::endl;
        va_end(va);
    }
}

void LogTotty::setLogPri(uint8_t pri)
{
    std::cout <<"current log priority is "<<priority<<", will to"<<pri<<std::endl;
    priority = pri;

}

LogTosyslog::LogTosyslog()
{
    openlog("[IPC_Serial]", LOG_PID|LOG_CONS, LOG_LOCAL0);
    setlogmask(LOG_UPTO(LOG_DEBUG));
}

LogTosyslog::~LogTosyslog()
{
    closelog();
}

void LogTosyslog::LogInfo(const char *stringFormat, ...) throw()
{
    va_list va;
    va_start(va,stringFormat);
    clock_gettime(CLOCK_MONOTONIC, &ts);
    vsprintf(logMsg, stringFormat, va);
    syslog(LOG_INFO, "[%ld.%ld]%s", ts.tv_sec, ts.tv_nsec,logMsg);
    va_end(va);
}

void LogTosyslog::LogDebug(const char *stringFormat, ...) throw()
{

    va_list va;
    va_start(va,stringFormat);
    clock_gettime(CLOCK_MONOTONIC, &ts);
    vsprintf(logMsg, stringFormat, va);
    syslog(LOG_DEBUG, "[%ld.%ld]%s", ts.tv_sec, ts.tv_nsec,logMsg);
    va_end(va);
}

void LogTosyslog::LogWarning(const char *stringFormat, ...) throw()
{
    va_list va;
    va_start(va,stringFormat);
    clock_gettime(CLOCK_MONOTONIC, &ts);
    vsprintf(logMsg, stringFormat, va);
    syslog(LOG_WARNING, "[%ld.%ld]%s", ts.tv_sec, ts.tv_nsec,logMsg);
    va_end(va);
}

void LogTosyslog::LogError(const char *stringFormat, ...) throw()
{

    va_list va;
    va_start(va,stringFormat);
    clock_gettime(CLOCK_MONOTONIC, &ts);
    vsprintf(logMsg, stringFormat, va);
    syslog(LOG_ERR, "[%ld.%ld]%s", ts.tv_sec, ts.tv_nsec,logMsg);
    va_end(va);
}

void LogTosyslog::setLogPri(uint8_t pri)
{
    LogInfo("current log priority will upto %d", pri);
    setlogmask(LOG_UPTO(pri));
}
