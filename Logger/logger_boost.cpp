//
// Created by hengsheng on 11/21/17.
//

#include "logger_boost.h"

namespace LOGTEST
{
    Logger_boost::Logger_boost()
    {
        logging::add_file_log("./logs/boost.txt");
        logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
        logging::add_common_attributes();
        logger = new src::basic_logger();
    }

    Logger_boost::~Logger_boost()
    {
        delete logger;
    }

    Logger_boost& Logger_boost::instance()
    {
        static Logger_boost instance;
        return instance;
    }

    void Logger_boost::log(const string &msg)
    {
        BOOST_LOG(*logger);
    }

    void Logger_boost::flush()
    {
        // todo
    }

    string Logger_boost::get_libname()
    {
        return "boost";
    }
}


