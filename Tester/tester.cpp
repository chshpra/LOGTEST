#include "tester.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <thread>
#include <chrono>

typedef std::chrono::duration<uint64_t, std::ratio<1, 1>> second;
typedef std::chrono::duration<uint64_t, std::ratio<1, 1000>> millisecond;
typedef std::chrono::duration<uint64_t, std::ratio<1, 1000000>> microsecond;

namespace LOGTEST
{
    Tester::Tester()
    {
    }

	void thread_func(Logger *logger, const int &thread, const int &num_logs, std::vector<bool> *thread_states)
	{
		for (int i = 0; i < num_logs; ++i)
		{
			char msg[100];
			sprintf_s(msg, "this is a test message; thread#: %d; log#: %d;", thread, i);
			logger->log(msg);
		}

		(*thread_states)[thread] = true;
	}

    void Tester::run_performance_test(Logger &logger, const int &num_threads, const int &logs_per_thread)
    {
	std::vector<bool> thread_states(num_threads, false);
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_threads; ++i)
        {
            std::thread new_thread(thread_func, &logger, i, logs_per_thread, &thread_states);
            new_thread.detach();
        }
		// check if all threads are finished
		auto iter = thread_states.begin();
		while (iter != thread_states.end())
		{
			if (*iter == true) ++iter;
			Sleep(1);	// todo: changed to linux version
		}
        auto end_time = std::chrono::high_resolution_clock::now();
	    uint64_t duration_us = std::chrono::duration_cast<microsecond>(end_time - start_time).count();

        print_result(logger.get_libname(), num_threads, logs_per_thread, duration_us);
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
		string parttern = ".*thread#: ([0-9])+.*log#: ([0~9])+;$";
		std::regex reg_pattern(parttern, std::regex::grep);
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

    void Tester::print_header()
    {
        std::cout << std::setw(10) << std::left << "name"
                  << std::setw(10)  << std::left << "thread"
                  << std::setw(15) << std::left << "logs/thread"
                  << std::setw(15) << std::left << "total logs"
                  << std::setw(15)  << std::left << "time(in secs)"
                  << std::setw(15) << std::left << "Avg. logs/sec"
                  << std::setw(15) << std::left << "Avg. ns/log"
                  << std::endl;
    }

    void Tester::print_result(const string &lib_name, const int &num_threads, const int &logs_per_thread, const double &duration_us)
    {
        std::cout << std::setw(10) << std::left << lib_name
                  << std::setw(10) << std::left << num_threads
                  << std::setw(15) << std::left << logs_per_thread
                  << std::setw(15) << std::left << num_threads * logs_per_thread
                  << std::setw(15) << std::left << std::setprecision(5) << duration_us / 1E6
                  << std::setw(15) << std::left << std::setprecision(5) << (num_threads * logs_per_thread) / (duration_us / 1E6)
                  << std::setw(15) << std::left << std::setprecision(5) << duration_us * 1E3 / (num_threads * logs_per_thread)
                  << std::endl;
    }
}
