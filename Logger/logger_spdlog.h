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

		void log(const string &msg);
		void log_mt(const string &msg);
		string get_libname();

	private:
		Logger_spdlog();
		std::shared_ptr<spdlog::logger> spdlogger_mt;
		std::shared_ptr<spdlog::logger> spdlogger_st;
	};
}
