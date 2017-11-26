#include "tester.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <regex>
#include <thread>
#include <numeric>
#include <cmath>
#include <mutex>
#include <unistd.h>
#include <fstream>

typedef std::chrono::duration<uint64_t, std::ratio<1, 1>> second;
typedef std::chrono::duration<uint64_t, std::ratio<1, 1000>> millisecond;
typedef std::chrono::duration<uint64_t, std::ratio<1, 1000000>> microsecond;
typedef std::chrono::duration<uint64_t, std::ratio<1, 1000000000>> nanosecond;

namespace LOGTEST
{
    Tester::Tester()
    {
    }

	void thread_func_overall(Logger *logger, const int &thread, const int &num_logs, std::vector<bool> *thread_states)
	{
		for (int i = 0; i < num_logs; ++i)
		{
			// char msg[100];
			// sprintf(msg, "this is a test message; thread#: %d; log#: %d;", thread, i);
            // logger->log(msg);
		    logger->log("this is a test message");
        }

		(*thread_states)[thread] = true; // mark thread completed
	}

    uint64_t overall_performance_test(Logger &logger, const int &num_threads, const int &logs_per_thread)
    {
        std::vector<bool> thread_states(num_threads, false);
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_threads; ++i)
        {
            std::thread new_thread(thread_func_overall, &logger, i, logs_per_thread, &thread_states);
            new_thread.detach();
        }
        // check if all threads are finished
        auto iter = thread_states.begin();
        while (iter != thread_states.end())
        {
            if (*iter == true) ++iter;
            usleep(1000);
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        uint64_t duration_ns = std::chrono::duration_cast<nanosecond>(end_time - start_time).count();
        return duration_ns;
    }

    void Tester::run_overall_performance_test(Logger &logger, const int &num_threads, const int &logs_per_thread)
    {
        // flush previous logs to avoid interference
        logger.flush();

        uint64_t duration_ns = overall_performance_test(logger, num_threads, logs_per_thread);

        print_result_overall(logger.get_libname(), num_threads, logs_per_thread, duration_ns);
    }

    std::mutex mtx;

    void thread_func_latency(Logger *logger, const int &thread, const int &num_logs, std::vector<bool> *thread_states,
                             std::vector<uint64_t> *cost_vector)
    {
        for (int i = 0; i < num_logs; ++i)
        {
            auto start_time = std::chrono::high_resolution_clock::now();
            logger->log("this is a test message");
            auto end_time = std::chrono::high_resolution_clock::now();
            uint64_t duration_ns = std::chrono::duration_cast<nanosecond>(end_time - start_time).count();
            std::lock_guard<std::mutex> lock(mtx);
            cost_vector->push_back(duration_ns);
        }

        (*thread_states)[thread] = true; // mark completed
    }

    void latency_test(Logger &logger, const int &num_threads, const int &logs_per_thread,
                      std::vector<uint64_t> *log_cost)
    {
        std::vector<bool> thread_states(num_threads, false);
        for (int i = 0; i < num_threads; ++i)
        {
            std::thread new_thread(thread_func_latency, &logger, i, logs_per_thread, &thread_states, log_cost);
            new_thread.detach();
        }

        // check if all threads are finished
        auto iter = thread_states.begin();
        while (iter != thread_states.end())
        {
            if (*iter == true)
                ++iter;
            usleep(1000);
        }
    }

    uint64_t std_deviation(std::vector<uint64_t> &samples, const uint64_t &mean)
    {
        uint64_t sum = 0;

        for (auto iter = samples.cbegin(); iter != samples.cend(); ++iter)
        {
            sum += (*iter - mean) * (*iter - mean);
        }

        return std::sqrt(sum / (samples.size() - 1));
    }

    void Tester::run_latency_test(Logger &logger, const int &num_threads, const int &logs_per_thread)
    {
        // flush previous logs to avoid interference
        logger.flush();

        std::vector<uint64_t> cost_vector;
        latency_test(logger, num_threads, logs_per_thread, &cost_vector);

        uint64_t min_cost_us = *std::min_element(cost_vector.cbegin(), cost_vector.cend());
        uint64_t mean_cost_us = std::accumulate(cost_vector.cbegin(), cost_vector.cend(), (uint64_t)0) / cost_vector.size();
        uint64_t max_cost_us = *std::max_element(cost_vector.cbegin(), cost_vector.cend());
        uint64_t sigma_cost = std_deviation(cost_vector, mean_cost_us);
        print_result_latency(logger.get_libname(), num_threads, logs_per_thread, min_cost_us, mean_cost_us, max_cost_us, sigma_cost);

        // save for further analysis
        // save_cost_to_file(logger.get_libname(), num_threads, &cost_vector);
    }

    void Tester::save_cost_to_file(const string &libname, const int &num_threads, std::vector<uint64_t> *cost_vector)
    {
        char file_name[100];
        sprintf(file_name, "./data/%s-%d.txt", libname.c_str(), num_threads);
        std::ofstream fs(file_name, std::ios::trunc);
        for (auto element : *cost_vector)
        {
            fs << element << std::endl;
        }
        fs.close();
    }

	bool Tester::run_thread_safety_test(Logger &logger)
	{
		std::cout << logger.get_libname() << "...... ";

		string file_name = logger.get_libname() + ".txt";
		std::ifstream in_stream(file_name);
		if (!in_stream)   
		{
			std::cout << "cant't find log file" << std::endl;
			return false;
		}
        
		string line;
		string pattern = ".*thread#: ([0-9])+.*log#: ([0~9])+;$";
		std::regex reg_pattern(pattern, std::regex::grep);
        std::smatch matches;
        while (getline (in_stream, line))
        {
            if (std::regex_match(line, reg_pattern))
            {
				std::cout << "failed. line: " << line << std::endl;
                return false;
            }
        }
        
        in_stream.close();
		
		std::cout << "passed" << std::endl;
        return true;
    }

    void Tester::print_header_overall()
    {
        std::cout << std::setw(10) << std::left << "name"
                  << std::setw(10) << std::left << "thread"
                  << std::setw(15) << std::left << "logs/thread"
                  << std::setw(15) << std::left << "total logs"
                  << std::setw(15) << std::left << "time(in secs)"
                  << std::setw(15) << std::left << "Avg. logs/sec"
                  << std::setw(15) << std::left << "Avg. ns/log"
                  << std::endl;
    }

    void Tester::print_result_overall(const string &lib_name, const int &num_threads, const int &logs_per_thread,
                                      const uint64_t &duration_ns)
    {
        double duration_s = duration_ns / 1E9;
        double duration_ms = duration_ns / 1E6;
        double duration_us = duration_us / 1E3;
        int total_logs = num_threads * logs_per_thread;

        std::cout << std::setw(10) << std::left << lib_name
                  << std::setw(10) << std::left << num_threads
                  << std::setw(15) << std::left << logs_per_thread
                  << std::setw(15) << std::left << num_threads * logs_per_thread
                  << std::setw(15) << std::left << std::setprecision(5) << duration_s
                  << std::setw(15) << std::left << std::setprecision(5) << total_logs / duration_s
                  << std::setw(15) << std::left << std::setprecision(5) << duration_ns / total_logs
                  << std::endl;
    }

    void Tester::print_header_latency()
    {
        std::cout << std::setw(10) << std::left << "name"
                  << std::setw(10) << std::left << "thread"
                  << std::setw(15) << std::left << "logs/thread"
                  << std::setw(15) << std::left << "total logs"
                  << std::setw(15) << std::left << "min ns/log"
                  << std::setw(15) << std::left << "avg. ns/log"
                  << std::setw(15) << std::left << "max ns/log"
                  << std::setw(15) << std::left << "std. deviation"
                  << std::endl;
    }

    void Tester::print_result_latency(const string &lib_name, const int &num_threads, const int &logs_per_thread,
                                      const uint64_t &min_ns, const uint64_t &mean_ns, const uint64_t &max_ns, const uint64_t &sigma)
    {
        std::cout << std::setw(10) << std::left << lib_name
                  << std::setw(10) << std::left << num_threads
                  << std::setw(15) << std::left << logs_per_thread
                  << std::setw(15) << std::left << num_threads * logs_per_thread
                  << std::setw(15) << std::left << min_ns
                  << std::setw(15) << std::left << mean_ns
                  << std::setw(15) << std::left << max_ns
                  << std::setw(15) << std::left << sigma
                  << std::endl;
    }
}
