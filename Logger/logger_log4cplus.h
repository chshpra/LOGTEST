//
// Created by hengsheng on 11/20/17.
//

#ifndef LOG_TEST_LOGGER_LOG4CPLUS_H
#define LOG_TEST_LOGGER_LOG4CPLUS_H

#include "logger.h"
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/loggingmacros.h>

namespace LOGTEST
{
    class Logger_log4cplus : public Logger
    {
    public:
        static Logger_log4cplus& instance();

        void log(const string &msg) override ;
        void flush() override ;
        string get_libname() override ;

    private:
        Logger_log4cplus();

        log4cplus::SharedAppenderPtr pFileAppender;
        log4cplus::Logger logger;
    };
}


#endif //LOG_TEST_LOGGER_LOG4CPLUS_H
