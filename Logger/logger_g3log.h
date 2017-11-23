//
// Created by hengsheng on 11/22/17.
//

#ifndef LOG_TEST_LOGGER_G3LOG_H
#define LOG_TEST_LOGGER_G3LOG_H

#include "logger.h"
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>

namespace LOGTEST
{
    class Logger_g3log : public Logger
    {
    public:
        static Logger_g3log& instance();

        void log(const string &msg) override;
        void flush() override;
        string get_libname() override;

    private:
        Logger_g3log();
        std::unique_ptr<g3::LogWorker> worker;
        std::unique_ptr<g3::FileSinkHandle> defaultHandle;
    };
}

#endif //LOG_TEST_LOGGER_G3LOG_H
