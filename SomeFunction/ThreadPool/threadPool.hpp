/**
 * @file threadPool.hpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <future>
#include <functional>
#include <queue>
#include <vector>

constexpr unsigned int THREAD_POOL_MAX = 16;// should be cpu cores * 2;

class ThreadPool {
    using Task = std::function<void()>;

    std::atomic<bool>           isRunning{false};
    std::vector<std::thread>    m_threads;
    std::queue<Task>            m_tasks;

public:
    /**
     * @brief Construct a new Thread Pool object
     * 
     * @param size :thread pool size
     */
    ThreadPool(unsigned size = 4) {
        size = std::min(size, THREAD_POOL_MAX);
        if (size == 0)
            throw std::runtime_error("thread pool max size should large than 0\n");
        isRunning.store(true);
        startThread(size);
    }

    /**
     * @brief Destroy the Thread Pool object
     * 
     */
    ~ThreadPool() {
        isRunning.store(false);
        m_cv.notify_all();
        for (std::thread& th : m_threads) {
            if (th.joinable())
                th.join();
        }
    }

    /**
     * @brief set function to thread pool
     * 
     * @tparam Function : 
     * @tparam ArgTypes : function's input argument types
     * @param f         : function
     * @param args      : input arguments
     * @return auto     : output type future
     */
    template<typename Function, typename...ArgTypes>
    auto attach(Function&& f, ArgTypes&&... args) {
        using ReturnType = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<Function>(f), std::forward<ArgTypes>(args)...));
        auto future = task->get_future();
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            m_tasks.emplace([task](){(*task)();});
        }
        m_cv.notify_one();
        return future;
    }

private:
    mutable std::mutex m_mutex;
    std::condition_variable m_cv;

    /**
     * @brief start thread
     * 
     * @param size size of thread pool
     */
    void startThread(unsigned size) {
        for (/*alread init*/; size > 0; --size) {
            m_threads.emplace_back([this](){
                while (isRunning.load()) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lg(m_mutex);
                        m_cv.wait(lg, [this] {
                            return !m_tasks.empty() || !isRunning.load();
                        });
                        if (!isRunning.load() || m_tasks.empty())
                            return;
                        task = std::move(m_tasks.front());
                        m_tasks.pop();
                    }
                    task();
                }
            });
        }
    }
};
