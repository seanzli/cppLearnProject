#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <vector>

class ThreadFor {
public:
    ThreadFor(unsigned _thread_num = 4) : thread_num(_thread_num) {}

    template<typename Func, typename OutIterator, typename... InIterator>
    void run(Func fun, size_t size, OutIterator _out_itr, InIterator... _in_itr) {
        for (size_t i = 0; i < size; ++i) {
            *(_out_itr + i) = fun((*(_in_itr + i))...);
        }
    }

    template<typename Func, typename OutIterator, typename... InIterator>
    void run_cv(Func fun, size_t size, OutIterator _out_itr, InIterator... _in_itr) {
        std::mutex mutex;
        std::condition_variable cv;
        std::vector<std::thread> th_vec;
        std::atomic<bool> running{true};
        volatile size_t cur = 0;
        for (unsigned i = 0; i < thread_num; ++i) {
            th_vec.emplace_back(
                [&] {
                    while (cur < size && running.load()) {
                        std::unique_lock<std::mutex> ul(mutex);
                        cv.wait(ul, [&]{return running.load();});
                        if (!running.load())
                            return;
                        size_t idx = cur++;
                        cv.notify_one();
                        *(_out_itr + idx) = fun((*(_in_itr + idx))...);
                    }
                    cv.notify_all();
                }
            );
        }

        cv.notify_one();
        for (auto& th : th_vec) {
            th.join();
        }
        return;
    }

    template<typename Func, typename OutIterator, typename... InIterator>
    void run_mutex(Func fun, size_t size, OutIterator _out_itr, InIterator... _in_itr) {
        std::mutex mutex;
        std::vector<std::thread> th_vec;
        volatile size_t cur = 0;
        for (unsigned i = 0; i < thread_num; ++i) {
            th_vec.emplace_back(
                [&] {
                    while (cur < size) {
                        mutex.lock();
                        size_t idx = cur++;
                        mutex.unlock();
                        if (idx >= size)
                            return;
                        *(_out_itr + idx) = fun((*(_in_itr + idx))...);
                    }
                }
            );
        }

        for (auto& th : th_vec) {
            th.join();
        }
        return;
    }



private:
    unsigned thread_num;
};