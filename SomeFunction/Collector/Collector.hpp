#pragma once

#include <iostream>

#include <memory>
#include <vector>
#include <future>
#include <list>

#include "Observer.hpp"

using ptrObserver   = std::shared_ptr<Observer>;
using container     = std::list<ptrObserver>;

class ICollector {
public:
    virtual ~ICollector() {}
    virtual void parser() = 0;

    void attach(ptrObserver obs) {
        m_list.emplace_back(obs);
    }

    void notify() {
        typename container::const_iterator itr;
        std::cout << "list size:" << m_list.size() << std::endl;
        for (itr = m_list.cbegin(); itr != m_list.cend(); itr++) {
            if ((*itr).get() != nullptr)
                (*itr)->update();
            else
                std::cout << "itr nullptr\n";
        }
    }

private:
    container m_list;
};

class Velodyne : public ICollector {
public:
    void parser() override {
        std::cout << "Velodyne: parser\n";
        notify();
    }
};

class CollectorManager {
public:
    CollectorManager() {}
    ~CollectorManager() {
        for (auto& th : m_threads) {
            if (th.joinable())
                th.join();
        }
    }

    template<typename T>
    void add(T&& __collector) {
        auto th = [](T&& __collector) mutable { __collector.parser(); };
        m_threads.emplace_back(
            std::thread(th, std::move(__collector))
        );
    }

private:
    std::vector<std::thread> m_threads;
};