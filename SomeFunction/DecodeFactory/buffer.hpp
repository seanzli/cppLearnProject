#pragma once

#include <deque>
#include <mutex>
#include <vector>

/**
 * @brief output buffer
 * 
 * @tparam T  // data type
 */
template<typename T>
class Buffer {
public:
    Buffer() {}
    ~Buffer() {}

    bool empty() {
        std::lock_guard<std::mutex> lg(m_mutex);
        return m_data.empty();
    }

    size_t size() {
        std::lock_guard<std::mutex> lg(m_mutex);
        return m_data.size();
    }

    void push_back(const T& val) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_data.push_back(val);
    }

    T pop_front() {
        std::lock_guard<std::mutex> lg(m_mutex);
        T val = m_data.front();
        m_data.pop_front();
        return val;
    }

    void push_front(std::vector<T>& vec) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_data.insert(m_data.begin(), vec.begin(), vec.end());
    }

    void push_back(std::vector<T>& vec) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_data.insert(m_data.end(), vec.begin(), vec.end());
    }

    void swap(std::deque<T>& que) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_data.swap(que);
    }

private:
    std::deque<T>   m_data;
    std::mutex      m_mutex;
};