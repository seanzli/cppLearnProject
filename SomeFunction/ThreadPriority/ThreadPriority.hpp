#pragma once

#include <thread>

constexpr uint8_t THREAD_PRIORITY_MAX = 99;
constexpr uint8_t THREAD_PRIORITY_MIN = 1;

class Thread {
public:
    Thread() = default;

    static void getPriority(std::thread& th, int& _policy, int& _priority) {
        struct sched_param para;
        pthread_getschedparam(th.native_handle(), &_policy, &para);
        _priority = para.sched_priority;
    }
    static void setPriority(std::thread& th, int _policy, int _priority) {
        struct sched_param para;
        _priority =  _priority > THREAD_PRIORITY_MAX ? THREAD_PRIORITY_MAX : _priority;
        _priority =  _priority < THREAD_PRIORITY_MIN ? THREAD_PRIORITY_MIN : _priority;
        para.sched_priority = _priority;
        pthread_setschedparam(th.native_handle(), _policy, &para);
    }
};