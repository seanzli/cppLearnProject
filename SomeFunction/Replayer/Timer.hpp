#pragma once

#include <chrono>
#include <atomic>
#include <list>

#include "../CommandWithThreadPool/CommandWithThreadPool.hpp"

#include <glog/logging.h>

class Timer {
public:
    static Timer& getInstance() {
        static Timer m_timer;
        return m_timer;
    }

    void setCycle(unsigned millisec = 1000) {m_cycle_millisec = millisec;}

    void attach(std::function<void()> func) {
        m_list.push_back(func);
        DLOG(INFO) << "add func, list size() = " << m_list.size();
    }

    auto run() {return std::thread([&]{start();});}

    void terminate() {m_running.store(false);}

private:
    Timer() {}
    ~Timer() {terminate();}

    std::atomic<bool> m_running{true};
    unsigned m_cycle_millisec = 1000; // unit = ms;
    std::list<std::function<void()>> m_list;

    void start() {
        while (m_running.load()) {
            
            std::this_thread::sleep_for(
                std::chrono::milliseconds(m_cycle_millisec));
            
            for (auto& itr : m_list) {
                (itr)();
            }
        }
    }
};