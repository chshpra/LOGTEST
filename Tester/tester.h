#pragma once
#include "../Logger/logger.h"

namespace LOGTEST
{
    class Tester
    {
    public:
        Tester();

        double test_single_thread(Logger& logger, const int &num_logs = 10e6);
        double test_multi_thread(Logger& logger, const int &num_threads = 10, const int &logs_per_thread = 10e5);
        void print_header();

    private:
        void log_loop(Logger &logger, const int &num_iters);
        bool check_thread_safety(const string &libname);
        void print_result(const string &lib_name, const int &num_threads, const int &logs_per_thread, const double &secs, bool is_multi_thread_safe);
    };
}
