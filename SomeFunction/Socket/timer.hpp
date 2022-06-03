#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>
#include <thread>

namespace SocketClass {
    class Timer {
    public:
        explicit Timer(int msec = 5000)
            : m_dif(msec)
            , start(std::chrono::system_clock::now()) {}

        /**
         * check the timer is stil valid or not;
         * @return
         */
        bool valid() {
            auto dif = std::chrono::duration_cast<std::chrono::milliseconds>(
                    start - std::chrono::system_clock::now());
            return dif.count() < m_dif;
        }
    private:
        int m_dif;
        std::chrono::system_clock::time_point start;
    };
}


#endif // _TIMER_H_