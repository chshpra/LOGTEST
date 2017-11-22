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
		int queue_size = pow(2, 20);	// queue size must be a power of two
		spdlog::set_async_mode(queue_size); 
		logger = spdlog::basic_logger_mt("logger", "spdlog.txt", true);
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
