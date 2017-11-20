#pragma once
#include <string>

using std::string;

namespace LOGTEST
{
	class Logger
	{
	public:
		Logger() { };
		virtual ~Logger() { };
		
		virtual void log(const string &msg) = 0;		// implement the fastest logging method
		virtual void log_mt(const string &msg) = 0;		// implement the fastest thread-safe logging method
		virtual string get_libname() = 0;					// return the logger's library name
	};
}
