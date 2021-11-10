#include <iostream>
#include "Timer.hpp"

#include "glog/logging.h"

void func1() {
    auto now = std::chrono::system_clock::now();
    std::time_t cur_time = std::chrono::system_clock::to_time_t(now);
    std::cout << "Func1 thread id = " << std::this_thread::get_id() 
              << " cur time : " << cur_time
              << std::endl;
}

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir = "../log";
    FLAGS_logtostderr = true;

    DLOG(INFO) << "start";

    auto& timer = Timer::getInstance();

    timer.attach([]{func1();});

    timer.run();
    std::this_thread::sleep_for(std::chrono::seconds(10));

    timer.terminate();

    std::cout << "terminate\n";

    return 0;
}