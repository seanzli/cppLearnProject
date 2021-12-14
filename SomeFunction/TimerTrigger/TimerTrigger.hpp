#include <chrono>
#include <list>
#include <functional>
#include <atomic>
#include <vector>
#include <thread>
#include <future>

class TimerTrigger {
    using Func = std::function<void()>;
public:
    explicit TimerTrigger(double gap = 1.0) : m_gap(gap) {}
    template<typename F, typename...ArgsType>
    void attach(F&& f, ArgsType&&...args) {
        Func func = std::bind(std::forward<F>(f), std::forward<ArgsType>(args)...);
        m_actions.template emplace_back(func);
    }

    std::thread run() {
        return std::thread([&] {
            m_running.store(true);
            for (auto &itr: m_actions) {
                m_threads.emplace_back([&] {
                    while (m_running.load()) {
                        std::unique_lock <std::mutex> ul(m_mutex);
                        m_cv.wait(ul, [&] {
                            return !m_running.load() || m_trigger.load();
                        });
                        m_trigger.store(false);
                        if (!m_running.load())
                            return;
                        itr();
                    }
                });
            }
            while (m_running.load()) {
                std::this_thread::sleep_for(std::chrono::microseconds(
                        static_cast<long>(m_gap * 1000000)
                ));
                m_trigger.store(true);
                m_cv.notify_all();
            }
        });
    }
    void terminate() {
        m_running.store(false);
        m_cv.notify_all();
        for (auto& th : m_threads) {
            if (th.joinable())
                th.join();
        }
    }

private:
    double m_gap;
    std::list<Func> m_actions;
    std::atomic<bool> m_running{false};
    std::atomic<bool> m_trigger{false};
    std::vector<std::thread> m_threads;
    std::condition_variable m_cv;
    std::mutex  m_mutex;
};
