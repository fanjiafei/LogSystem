#ifndef LOGSYSTEM_H
#define LOGSYSTEM_H

#include <stdint.h>
#include <sys/time.h>

/*-------------------color-------------------------------------*/
#define NONE         "\033[m"
#define RED          "\033[0;32;31m"
#define LIGHT_RED    "\033[1;31m"
#define GREEN        "\033[0;32;32m"
#define LIGHT_GREEN  "\033[1;32m"
#define BLUE         "\033[0;32;34m"
#define LIGHT_BLUE   "\033[1;34m"
#define DARY_GRAY    "\033[1;30m"
#define CYAN         "\033[0;36m"
#define LIGHT_CYAN   "\033[1;36m"
#define PURPLE       "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN        "\033[0;33m"
#define YELLOW       "\033[1;33m"
#define LIGHT_GRAY   "\033[0;37m"
#define WHITE        "\033[1;37m"
/*--------------------color------------------------------------*/


enum LogMode
{
    OUTPUT_TO_TTY = 0,
    OUTPUT_TO_SYSLOG,
};

enum SysLog
{
    LOG_EMERG = 0,	/* system is unusable */
	LOG_ALERT = 1,	/* action must be taken immediately */
    LOG_CRIT  = 2,	/* critical conditions */
    LOG_ERR	  = 3,	/* error conditions */
	LOG_WARNING	= 4,	/* warning conditions */
	LOG_NOTICE	= 5,	/* normal but significant condition */
	LOG_INFO  = 6,	/* informational */
	LOG_DEBUG = 7,	/* debug-level messages */
};

class LogSystem
{
public:
    LogSystem();
    virtual ~LogSystem();
    virtual void LogInfo(const char *stringFormat, ...) throw();
    virtual void LogDebug(const char *stringFormat, ...) throw();
    virtual void LogWarning(const char *stringFormat, ...) throw();
    virtual void LogError(const char *stringFormat, ...) throw();
    virtual void setLogPri(uint8_t pri);
    static LogSystem* getInstance();

};

extern LogSystem* logHandler;

class LogTotty:public LogSystem
{
public:
    LogTotty();
    virtual void LogInfo(const char *stringFormat, ...) throw();
    virtual void LogDebug(const char *stringFormat, ...) throw();
    virtual void LogWarning(const char *stringFormat, ...) throw();
    virtual void LogError(const char *stringFormat, ...) throw();
    virtual void setLogPri(uint8_t pri);

private:
    int priority;
    struct timespec ts;
    char logMsg[1024];
};

class LogTosyslog:public LogSystem
{
public:
    LogTosyslog();
    virtual ~LogTosyslog();
    virtual void LogInfo(const char *stringFormat, ...) throw();
    virtual void LogDebug(const char *stringFormat, ...) throw();
    virtual void LogWarning(const char *stringFormat, ...) throw();
    virtual void LogError(const char *stringFormat, ...) throw();
    virtual void setLogPri(uint8_t pri);

private:
    struct timespec ts;
    char logMsg[1024];
};


#endif
