//
// Created by hengsheng on 11/21/17.
//

#include "logger_log4cplus.h"

namespace LOGTEST
{
    Logger_log4cplus::Logger_log4cplus() :
            pFileAppender(new log4cplus::FileAppender("./logs/log4cplus.txt"))
    {
        pFileAppender->setName("log4cplus_file_appender");
        logger = log4cplus::Logger::getInstance("log4cplus");
        logger.addAppender(pFileAppender);
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

    void Logger_log4cplus::flush()
    {
        // todo
    }

    string Logger_log4cplus::get_libname()
    {
        return "log4cplus";
    }
}

