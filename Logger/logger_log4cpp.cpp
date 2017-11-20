#include "logger_log4cpp.h"

namespace LOGTEST
{
	Logger_log4cpp::Logger_log4cpp() 
	{
		log4cpp::Appender *appender = new log4cpp::FileAppender("default", "./logs/log4cpp.txt");
		appender->setLayout(new log4cpp::BasicLayout());
		logger = &log4cpp::Category::getRoot();
		logger->setPriority(log4cpp::Priority::INFO);
		logger->addAppender(appender);
	}

	Logger_log4cpp& Logger_log4cpp::instance() 
	{
		static Logger_log4cpp instance;
		return instance;
	}

	void Logger_log4cpp::log(const string &msg) 
	{
		logger->info(msg);
	}

	void Logger_log4cpp::log_mt(const string &msg) 
	{
		logger->info(msg);
	}

	string Logger_log4cpp::get_libname()
	{
		return "log4cpp";
	}
}
