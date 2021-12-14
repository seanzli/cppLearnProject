#include "TimerTrigger.hpp"

int main() {
    TimerTrigger trigger;
    auto th = [] {printf("trigger\n");};
    trigger.attach(th);
    auto t = trigger.run();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    trigger.terminate();
    std::this_thread::sleep_for(std::chrono::milliseconds (1));
    return 0;
}
