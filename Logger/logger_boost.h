//
// Created by hengsheng on 11/21/17.
//

#ifndef LOG_TEST_LOGGER_BOOST_H
#define LOG_TEST_LOGGER_BOOST_H

#include "logger.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace LOGTEST
{
    class Logger_boost : public Logger
    {
    public:
        static Logger_boost& instance();
        ~Logger_boost() override;

        void log(const string &msg) override ;
        void flush() override ;
        string get_libname() override ;

    private:
        Logger_boost();
        src::severity_logger_mt *logger;
    };
}

#endif //LOG_TEST_LOGGER_BOOST_H
