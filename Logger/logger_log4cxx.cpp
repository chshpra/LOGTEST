#include "logger_log4cxx.h"

namespace LOGTEST
{
	Logger_log4cxx::Logger_log4cxx()
	{
		logger = log4cxx::Logger::getRootLogger();
		log4cxx::PropertyConfigurator::configureAndWatch("log4cxx.properties");
	}

	Logger_log4cxx& Logger_log4cxx::instance()
	{
		static Logger_log4cxx instance;
		return instance;
	}

	void Logger_log4cxx::log(const string &msg)
	{
		LOG4CXX_INFO(logger, msg);
	}

	void Logger_log4cxx::flush()
    {
    }

	string Logger_log4cxx::get_libname()
	{
		return "log4cxx";
	}
}
