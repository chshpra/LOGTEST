#pragma once
#include "../Logger/logger.h"

namespace LOGTEST
{
    class Tester
    {
    public:
        Tester();

        void run_performance_test(Logger &logger, const int &num_threads, const int &logs_per_thread);
        bool run_thread_safety_test(Logger &logger);
        void print_header();

    private:
        void print_result(const string &lib_name, const int &num_threads, const int &logs_per_thread, const double &secs);
    };
}
