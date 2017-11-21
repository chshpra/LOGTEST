#include "Tester/tester.h"
#include "Logger/logger_spdlog.h"
#include "Logger/logger_log4cpp.h"
#include "Logger/logger_log4cxx.h"
#include "Logger/logger_log4cplus.h"

using namespace LOGTEST;

int main()
{
    // init loggers
    Logger_spdlog &spdlog = Logger_spdlog::instance();
    Logger_log4cpp &log4cpp = Logger_log4cpp::instance();
    Logger_log4cxx &log4cxx = Logger_log4cxx::instance();
    Logger_log4cplus &log4cplus = Logger_log4cplus::instance();

    // init tester
    Tester tester;

    // 1. performance
    int total_logs = 1e6;
	std::cout << "Running performance test..." << std::endl;
	int test_cases[5] = { 1, 10, 20, 50, 100 };
	for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); ++i)
	{
		int threads = test_cases[i];
		int logs_per_threads = total_logs / threads;
		
		// print test information
		std::cout << "Scenario " << i + 1 << ":" << std::endl;
		tester.print_header();
		
		// add loggers here
		tester.run_performance_test(spdlog, threads, logs_per_threads);
        tester.run_performance_test(log4cpp, threads, logs_per_threads);
        tester.run_performance_test(log4cxx, threads, logs_per_threads);
        tester.run_performance_test(log4cplus, threads, logs_per_threads);
        
		sleep(2); // halt to avoid interference
		std::cout << std::endl;
	}

	// 2. thread safety
	std::cout << "Running thread safety test..." << std::endl;
	tester.run_thread_safety_test(spdlog);
	tester.run_thread_safety_test(log4cpp);
	tester.run_thread_safety_test(log4cxx);
	tester.run_thread_safety_test(log4cplus);

    return 0;
}


