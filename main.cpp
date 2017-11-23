#include "Tester/tester.h"
#include "Logger/logger_spdlog.h"
#include "Logger/logger_log4cpp.h"
#include "Logger/logger_log4cxx.h"
#include "Logger/logger_log4cplus.h"
#include "Logger/logger_glog.h"
#include "Logger/logger_g3log.h"

using namespace LOGTEST;

int main()
{
    // init loggers
    std::cout << "initiating loggers..." << std::endl;
    Logger_spdlog &spdlog = Logger_spdlog::instance();
    Logger_log4cpp &log4cpp = Logger_log4cpp::instance();
    Logger_log4cxx &log4cxx = Logger_log4cxx::instance();
    Logger_glog &glog = Logger_glog::instance();
    Logger_g3log &g3log = Logger_g3log::instance();

    // init tester
    std::cout << "initiating tester..." << std::endl << std::endl;
    Tester tester;

    // 1. performance
    int total_logs = 1e6;
    uint64_t delay= 1;
	std::cout << "1. Running overall performance test..." << std::endl;
	int test_cases[4] = { 1, 10, 20, 100 };
	for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); ++i)
	{
		int threads = test_cases[i];
		int logs_per_threads = total_logs / threads;
		
		// print test information
		std::cout << "Scenario " << i + 1 << ":" << std::endl;
        tester.print_header_overall();
		
		// add loggers here
        tester.run_overall_performance_test(spdlog, threads, logs_per_threads);
        usleep(delay);
        tester.run_overall_performance_test(log4cpp, threads, logs_per_threads);
        usleep(delay);
        tester.run_overall_performance_test(log4cxx, threads, logs_per_threads);
        usleep(delay);
        tester.run_overall_performance_test(glog, threads, logs_per_threads);
        usleep(delay);
        tester.run_overall_performance_test(g3log, threads, logs_per_threads);
        usleep(delay);
        // tester.run_overall_performance_test(log4cplus, threads, logs_per_threads);

        std::cout << std::endl;
    }

    // 2. latency
    std::cout << "2. Running latency test..." << std::endl;
    for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); ++i)
    {
        int threads = test_cases[i];
        int logs_per_threads = total_logs / threads;

        // print test information
        std::cout << "Scenario " << i + 1 << ":" << std::endl;
        tester.print_header_latency();

        // add loggers here
        tester.run_latency_test(spdlog, threads, logs_per_threads);
        usleep(delay);
        tester.run_latency_test(log4cpp, threads, logs_per_threads);
        usleep(delay);
        tester.run_latency_test(log4cxx, threads, logs_per_threads);
        usleep(delay);
        tester.run_latency_test(glog, threads, logs_per_threads);
        usleep(delay);
        tester.run_latency_test(g3log, threads, logs_per_threads);
        usleep(delay);

        std::cout << std::endl;
    }

	// 3. thread safety
	std::cout << "3. Running thread safety test..." << std::endl;
	tester.run_thread_safety_test(spdlog);
	tester.run_thread_safety_test(log4cpp);
	tester.run_thread_safety_test(log4cxx);
    tester.run_thread_safety_test(glog);
    tester.run_thread_safety_test(g3log);

    return 0;
}


