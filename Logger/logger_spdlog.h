#pragma once
#include "logger.h"
#include "spdlog/spdlog.h"
#include <memory>

namespace LOGTEST
{
	class Logger_spdlog : public Logger
	{
	public:
		static Logger_spdlog& instance();

		void log(const string &msg) override ;
		void flush() override ;
		string get_libname() override ;

	private:
		Logger_spdlog();
		//std::shared_ptr<spdlog::logger> logger;
        std::shared_ptr<spdlog::async_logger> logger;
    };
}
