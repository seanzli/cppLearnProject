#pragma once

#include <memory>
#include <unordered_set>
#include <functional>
#include <iostream>

#include "Buffer.hpp"

class BascDataTopic {
public:
    BascDataTopic() {}
    virtual ~BascDataTopic() {}
};

class DataSubscribe {
public:
    DataSubscribe() {}
    virtual ~DataSubscribe() {}
    
    virtual void getData(BascDataTopic*) = 0;
};

template<typename T>
class DataTopic : public BascDataTopic {
public:
    void attach(std::shared_ptr<DataSubscribe> sub) {
        m_set.insert(sub);
    }

    void notify() {
        for (auto& itr : m_set) {
            std::cout << "notify\n" << std::endl;
            itr->getData(this);
        }
    }

    Buffer<T>& getBufferReference() {
        return m_data;
    }

private:
    Buffer<T> m_data;
    std::unordered_set<std::shared_ptr<DataSubscribe>> m_set;
};

