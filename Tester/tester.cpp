#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <thread>
#include "tester.h"

namespace LOGTEST
{
    Tester::Tester()
    {
    }

    void Tester::log_loop(Logger &logger, const int &num_iters)
    {
        for (int i = 0; i < num_iters; ++i) 
        {
            char s[50];
            sprintf(s, "(st) this is a test message %d", i);
            logger.log(s);
        }
    }

    double Tester::test_single_thread(Logger &logger, const int &num_logs)
    {
        // test performance
        clock_t start = clock();
        this->log_loop(logger, num_logs);
        clock_t end = clock();
        double duration = (double)(end - start) / CLOCKS_PER_SEC;

        // test multi thread safety
        bool is_multi_thread_safe = check_thread_safety(logger.get_libname());

        print_result(logger.get_libname(), 1, num_logs, duration, is_multi_thread_safe);
        return duration;
    }

    void thread_func(Logger *logger, const int &thread, const int &num_iters)
    {
        for (int i = 0; i < num_iters; ++i)
        {
            char s[50];
            sprintf(s, "(mt) this is a test message %d %d", thread, i);
            logger->log_mt(s);
        }
    }

    double Tester::test_multi_thread(Logger &logger, const int &num_threads, const int &logs_per_thread)
    {
        // test performance
        clock_t start = clock();
        for (int i = 0; i < num_threads; ++i)
        {
            std::thread new_thread(thread_func, &logger, i, logs_per_thread);
            if (i == num_threads - 1 && new_thread.joinable())  // last thread
                new_thread.join();
            else
                new_thread.detach();
        }
        clock_t end = clock();
        double duration = (double)(end - start) / CLOCKS_PER_SEC;

        // test multi thread safety
        bool is_multi_thread_safe = check_thread_safety(logger.get_libname());

        // print result
        print_result(logger.get_libname(), num_threads, logs_per_thread, duration, is_multi_thread_safe);

        return duration;
    }

    bool Tester::check_thread_safety(const string &libname)
    {
        std::regex reg_pattern(".*message( [0-9]+)+", std::regex::basic);

        string file_name = "./logs/" + libname + ".txt";
        std::ifstream in_stream(file_name);
        if(in_stream)   // file exists
        {
            string line;
            std::smatch matches;
            while (getline (in_stream, line))
            {
                if (!std::regex_match(line, matches, reg_pattern))
                {
                    // std::cout << line << std::endl;
                    return false;
                }
            }
        }
        else
        {
            std::cout <<"failed to check thread safety. cant't find log file" << std::endl;
            return false;
        }

        in_stream.close();
        return true;
    }

    void Tester::print_header()
    {
        std::cout << std::setw(10) << std::left << "name"
                  << std::setw(10)  << std::left << "thread"
                  << std::setw(15) << std::left << "logs/thread"
                  << std::setw(15) << std::left << "total logs"
                  << std::setw(15)  << std::left << "time(in secs)"
                  << std::setw(15) << std::left << "Avg. logs/sec"
                  << std::setw(15) << std::left << "Avg. ns/log"
                  << std::setw(15) << std::left << "MTSafety"
                  << std::endl;
    }

    void Tester::print_result(const string &lib_name, const int &num_threads, const int &logs_per_thread, const double &secs, bool is_multi_thread_safe)
    {
        std::cout << std::setw(10) << std::left << lib_name
                  << std::setw(10) << std::left << num_threads
                  << std::setw(15) << std::left << logs_per_thread
                  << std::setw(15) << std::left << num_threads * logs_per_thread
                  << std::setw(15) << std::left << std::setprecision(5) << secs
                  << std::setw(15) << std::left << std::setprecision(5) << (num_threads * logs_per_thread) / secs
                  << std::setw(15) << std::left << std::setprecision(5) << secs / (num_threads * logs_per_thread) * 10e8
                  << std::setw(15) << std::left << is_multi_thread_safe
                  << std::endl;
    }
}
