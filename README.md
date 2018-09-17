# LogSystem
## 简介
- 封装一个通用日志系统，能够同时支持标准输出和syslog日志输出方式
- 当初始化日志系统时，判断环境变量LOGMODE，如果LOGMODE的值为syslog就选择syslog的日志打印方式，否则选择标准输出。
- 在选择标准输出时，通过环境变量LOGLEVEL可以设置日志的打印级别
