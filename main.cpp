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
    int delay = 2;
    int total_logs = 10e6; // ten million logs
    int threads, logs_per_threads;

    // scenario 1
    std::cout << "Scenario 1:" << std::endl;
    threads = 1;
    logs_per_threads = total_logs / threads;
    tester.print_header();
    tester.test_single_thread(spdlog, logs_per_threads);
    sleep(delay);   // halt to avoid interference
    tester.test_single_thread(log4cpp, logs_per_threads);
    sleep(delay);
    tester.test_single_thread(log4cxx, logs_per_threads);
    sleep(delay);
    tester.test_single_thread(log4cplus, logs_per_threads);
    sleep(delay);
    std::cout << std::endl;

    // scenario 2
    std::cout << "Scenario 2:" << std::endl;
    threads = 5;
    logs_per_threads = total_logs / threads;
    tester.print_header();
    tester.test_multi_thread(spdlog, threads, logs_per_threads);
    sleep(delay);
    tester.test_multi_thread(log4cpp, threads, logs_per_threads);
    sleep(delay);
    tester.test_multi_thread(log4cxx, threads, logs_per_threads);
    sleep(delay);
    tester.test_multi_thread(log4cplus, threads, logs_per_threads);
    sleep(delay);
    std::cout << std::endl;

    // scenario 3
    std::cout << "Scenario 3:" << std::endl;
    threads = 10;
    logs_per_threads = total_logs / threads;
    tester.print_header();
    tester.test_multi_thread(spdlog, threads, logs_per_threads);
    sleep(delay);
    tester.test_multi_thread(log4cpp, threads, logs_per_threads);
    sleep(delay);
    tester.test_multi_thread(log4cxx, threads, logs_per_threads);
    sleep(delay);
    tester.test_multi_thread(log4cplus, threads, logs_per_threads);
    sleep(delay);
    std::cout << std::endl;

    // scenario ...

    return 0;
}


