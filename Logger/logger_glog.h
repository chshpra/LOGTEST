//
// Created by hengsheng on 11/21/17.
//

#ifndef LOG_TEST_LOGGER_GLOG_H
#define LOG_TEST_LOGGER_GLOG_H

#include "logger.h"
#include <glog/logging.h>

namespace LOGTEST
{
    class Logger_glog : public Logger
    {
    public:
        static Logger_glog& instance();
        ~Logger_glog();

        void log(const string &msg) override;
        void flush() override;
        string get_libname() override;

    private:
        Logger_glog();
    };
}

#endif //LOG_TEST_LOGGER_GLOG_H
