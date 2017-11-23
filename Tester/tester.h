#pragma once
#include "../Logger/logger.h"
#include <vector>

namespace LOGTEST
{
    class Tester
    {
    public:
        Tester();

        void run_overall_performance_test(Logger &logger, const int &num_threads, const int &logs_per_thread);
        void run_latency_test(Logger &logger, const int &num_threads, const int &logs_per_thread);
        bool run_thread_safety_test(Logger &logger);

        void print_header_overall();
        void print_header_latency();

    private:
        void print_result_overall(const string &lib_name, const int &num_threads, const int &logs_per_thread,
                                  const uint64_t &duration_ns);
        void print_result_latency(const string &lib_name, const int &num_threads, const int &logs_per_thread,
                                  const uint64_t &min_ns, const uint64_t &mean_ns, const uint64_t &max_ns);
        void save_cost_to_file(const string &libname, const int &num_threads, std::vector<uint64_t> *cost_vector);
    };
}
