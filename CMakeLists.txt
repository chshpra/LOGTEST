cmake_minimum_required(VERSION 3.7)
project(log_test)

set(CMAKE_CXX_STANDARD 11)

include_directories(# for taurus.ai linux
                    /home/hcai/log_tools/spdlog/include/
                    /home/hcai/log_tools/log4cpp/include/
                    /home/hcai/log_tools/log4cxx/include/
                    # macbook
                    /usr/local/Cellar/spdlog/0.14.0/include/
                    /usr/local/Cellar/log4cpp/1.1.3/include/
                    /usr/local/Cellar/log4cplus/1.2.0/include/
                    /usr/local/Cellar/log4cxx/0.10.0_1/include/
                    /usr/local/Cellar/boost/1.65.1/include/
                    /usr/local/Cellar/glog/0.3.5_1/include/
                    /usr/local/Cellar/g3log/1.3/include/
                    # on vbox linux
                    /home/hengshen/Desktop/loglibs/spdlog/include/
                    /home/hengshen/Desktop/loglibs/log4cpp/include/
                    /home/hengshen/Desktop/loglibs/log4cxx/include/
                    )

set(SOURCE_FILES    main.cpp
                    Tester/tester.cpp
                    Logger/logger_log4cpp.cpp
                    Logger/logger_spdlog.cpp
                    Logger/logger_log4cxx.cpp
                    Logger/logger_log4cplus.cpp
                    Logger/logger_glog.cpp
                    Logger/logger_glog.h
                    Logger/logger_boost.cpp
                    Logger/logger_boost.h
        Logger/logger_g3log.cpp Logger/logger_g3log.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

link_directories(   # on my macbook
                    /usr/local/Cellar/log4cxx/0.10.0_1/lib/
                    /usr/local/Cellar/boost/1.65.1/lib/
                    /usr/local/Cellar/log4cpp/1.1.3/lib/
                    /usr/local/Cellar/log4cplus/1.2.0/lib/
                    /usr/local/Cellar/glog/0.3.5_1/lib/
                    /usr/local/Cellar/g3log/1.3/lib/
                    # on taurus.ai linux
                    /home/hcai/log_tools/log4cpp/lib/
                    /home/hcai/log_tools/log4cxx/lib/
                    # on vbox linux
                    /home/hengshen/Desktop/loglibs/log4cpp/lib/
                    /home/hengshen/Desktop/loglibs/log4cxx/lib/
                    )

TARGET_LINK_LIBRARIES(${PROJECT_NAME} log4cxx log4cpp log4cplus glog)
