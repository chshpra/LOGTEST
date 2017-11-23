#include "logger_spdlog.h"

namespace LOGTEST
{
	Logger_spdlog& Logger_spdlog::instance() 
	{
		static Logger_spdlog instance;
		return instance;
	}
	
	Logger_spdlog::Logger_spdlog() 
	{
//		size_t queue_size = pow(2, 20);	// queue size must be a power of two
//		spdlog::set_async_mode(queue_size);
//		logger = spdlog::basic_logger_mt("logger", "./logs/spdlog.txt", true);
        auto daily_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logfile", 23, 59);
        logger = std::make_shared<spdlog::async_logger>("mylogger", daily_sink, pow(2, 20));
	}

	void Logger_spdlog::log(const string &msg) 
	{
		logger->info(msg);
	}

	void Logger_spdlog::flush()
	{
		logger->flush();
	}

	string Logger_spdlog::get_libname()
	{
		return "spdlog";
	}
}
