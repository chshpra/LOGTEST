//
// Created by hengsheng on 11/21/17.
//

#include "logger_glog.h"

namespace LOGTEST
{
    Logger_glog::Logger_glog()
    {
        FLAGS_log_dir = "./logs/glog.txt";
        google::InitGoogleLogging("log_test");
        FLAGS_alsologtostderr = false;
    }

    Logger_glog::~Logger_glog()
    {
        google::ShutdownGoogleLogging();
    }

    Logger_glog& Logger_glog::instance()
    {
        static Logger_glog instance;
        return instance;
    }

    void Logger_glog::log(const string &msg)
    {
        LOG(INFO) << msg;
    }

    void Logger_glog::flush()
    {

    }

    string Logger_glog::get_libname()
    {
        return "glog";
    }
}
