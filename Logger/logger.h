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
		
		virtual void log(const string &msg) = 0;
		virtual void flush() = 0;
		virtual string get_libname() = 0;				// return the logger's library name
	};
}
