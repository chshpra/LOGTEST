//
// Created by hengsheng on 11/22/17.
//

#include "logger_g3log.h"

namespace LOGTEST
{
    Logger_g3log::Logger_g3log()
    {
        auto worker = g3::LogWorker::createLogWorker();
        auto defaultHandler = worker->addDefaultLogger("g3log", "./logs/");
        g3::initializeLogging(worker.get());
    }

    Logger_g3log& Logger_g3log::instance()
    {
        static Logger_g3log instance;
        return instance;
    }

    void Logger_g3log::log(const string &msg)
    {
        LOG(INFO) << msg;
    }

    void Logger_g3log::flush()
    {
    }

    string Logger_g3log::get_libname()
    {
        return "g3log";
    }
}