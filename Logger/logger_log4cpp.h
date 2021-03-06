#pragma once
#include "logger.h"
#include "log4cpp/Category.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/BasicLayout.hh"

namespace LOGTEST 
{
	class Logger_log4cpp : public Logger 
	{
	public:
		static Logger_log4cpp& instance();

		void log(const string &msg) override;
		void flush() override;
		string get_libname() override ;

	private:
		Logger_log4cpp();

		log4cpp::Category *logger;
	};
}
