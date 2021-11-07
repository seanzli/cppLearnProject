#include <iostream>
#include "Timer.hpp"

#include "glog/logging.h"

using namespace CommandSystem;

void func1() {
    auto now = std::chrono::system_clock::now();
    std::time_t cur_time = std::chrono::system_clock::to_time_t(now);
    std::cout << "Func1 thread id = " << std::this_thread::get_id() 
              << " cur time : " << cur_time
              << std::endl;
}

void registe(ManagerTP& manager) {
    manager.attach("func1", Command<>(func1));
}

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir = "../log";
    FLAGS_logtostderr = true;

    DLOG(INFO) << "start";

    ManagerTP manager(2);
    auto& timer = Timer::getInstance();
    registe(manager);

    timer.attach([&](){
        manager.execute("func1");
    });

    auto th = std::thread([&]{timer.run();});
    std::this_thread::sleep_for(std::chrono::seconds(10));

    timer.terminate();

    std::cout << "terminate\n";

    if (th.joinable()) {
        th.join();
    }

    return 0;
}