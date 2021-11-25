#include "ThreadPriority.hpp"

#include <future>
#include <iostream>

int main () {
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool running = false;

    std::thread th1 = std::thread(
        [&] {
            std::unique_lock<std::mutex> lg(m_mutex);
            m_cv.wait(lg, [&]{return running;});
            for (int i = 0; i < 100000; ++i)
                ;
            std::cout << "th1 is done\n";
        }
    );

    std::thread th2 = std::thread(
        [&] {
            std::unique_lock<std::mutex> ul(m_mutex);
            m_cv.wait(ul, [&]{return running;});
            for (int i = 0; i < 100000; ++i)
                ;
            std::cout << "th2 is done\n";
        }
    );

    Thread::setPriority(th1, SCHED_RR, 99);
    Thread::setPriority(th2, SCHED_RR, 1);
    
    running = true;
    m_cv.notify_all();

    th1.join();
    th2.join();

    return 0;
}