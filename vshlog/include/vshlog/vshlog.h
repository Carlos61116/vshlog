#include "vshlog/Logger.h"
#include "vshlog/Config.h"
#include "vshlog/Category.h"

#define VSH_INIT_DEV() \
    vsh::init(vsh::LogLevel::DEBUG); \
    vsh::add_console_sink(vsh::ConsoleSinkConfig{}); \
    vsh::add_file_sink(vsh::FileSinkConfig{ .append = true })

#define VSH_LOG(level, msg, cat)  vsh::log(level, msg, cat, __FILE__, __LINE__)
#define VSH_LOG_TRACE(msg, cat)   VSH_LOG(vsh::LogLevel::TRACE, msg, cat)
#define VSH_LOG_DEBUG(msg, cat)   VSH_LOG(vsh::LogLevel::DEBUG, msg, cat)
#define VSH_LOG_INFO(msg, cat)    VSH_LOG(vsh::LogLevel::INFO,  msg, cat)
#define VSH_LOG_WARN(msg, cat)    VSH_LOG(vsh::LogLevel::WARN,  msg, cat)
#define VSH_LOG_ERR(msg, cat)     VSH_LOG(vsh::LogLevel::ERR,   msg, cat)
#define VSH_LOG_FATAL(msg, cat)   VSH_LOG(vsh::LogLevel::FATAL, msg, cat)