//
// Created by hengsheng on 11/21/17.
//

#include "logger_log4cplus.h"

namespace LOGTEST
{
    Logger_log4cplus::Logger_log4cplus()
    {
        log4cplus::SharedAppenderPtr fileAppender(new log4cplus::FileAppender("./logs/log4cplus.txt"));
        logger = log4cplus::Logger::getInstance("base_logger");
        logger.addAppender(fileAppender);
    }

    Logger_log4cplus& Logger_log4cplus::instance()
    {
        static Logger_log4cplus instance;
        return instance;
    }

    void Logger_log4cplus::log(const string &msg)
    {
        LOG4CPLUS_INFO(logger, msg);
    }

    void  Logger_log4cplus::log_mt(const string &msg)
    {
        LOG4CPLUS_INFO(logger, msg);
    }

    string Logger_log4cplus::get_libname()
    {
        return "log4cplus";
    }
}

