#include "logger_spdlog.h"

namespace LOGTEST
{
	Logger_spdlog::Logger_spdlog() 
	{
		// create single thread logger
		spdlogger_st = spdlog::basic_logger_st("spdlogger_st", "./logs/spdlog.txt", false);
		// create multi-thread logger
		// the argument must be a power of 2, loggers created from now on will be in async mode
		spdlog::set_async_mode(8192);
		spdlogger_mt = spdlog::basic_logger_mt("spdlogger_mt", "./logs/spdlog.txt", false);
	}

	Logger_spdlog& Logger_spdlog::instance() 
	{
		static Logger_spdlog instance;
		return instance;
	}

	void Logger_spdlog::log(const string &msg) 
	{
		spdlogger_st->info(msg);
	}

	void Logger_spdlog::log_mt(const string &msg) 
	{
		spdlogger_mt->info(msg);
	}

	string Logger_spdlog::get_libname()
	{
		return "spdlog";
	}
}
