#pragma once

#include "logger.h"
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"

namespace LOGTEST
{
	class Logger_log4cxx : public Logger
	{
	public:
		static Logger_log4cxx& instance();

		void log(const string &msg) override ;
        void flush() override ;
		string get_libname() override ;
	
	private:
		Logger_log4cxx();

		log4cxx::LoggerPtr logger;
	};
}
