#pragma once
// c++ stl 11
#include <mutex>
#include <thread>
#include <queue>
#include <algorithm>

template<class T>
class Buffer {
public:
    Buffer() {};
    ~Buffer() {};

    size_t size() {
        std::lock_guard<std::mutex> lg(m_mutex);
        return m_buffer.size(); 
    }

    bool empty() {
        std::lock_guard<std::mutex> lg(m_mutex);
        return m_buffer.empty(); 
    }

    void setBufferSize(const unsigned long& buffer_size) {  m_buffer_length = buffer_size;  }

    void clear() {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_buffer.clear();
    }

    void push_back(const std::vector<T>& input) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_buffer.insert(m_buffer.end(), input.begin(), input.end());
        if (m_buffer.size() > m_buffer_length)
            m_buffer.erase(m_buffer.begin(), m_buffer.end() - m_buffer_length);
    }
    
    void push_back(const std::deque<T>& input) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_buffer.insert(m_buffer.end(), input.begin(), input.end());
        if (m_buffer.size() > m_buffer_length)
            m_buffer.erase(m_buffer.begin(), m_buffer.end() - m_buffer_length);
    }

    size_t copy(std::vector<T>& output) {
        std::lock_guard<std::mutex> lg(m_mutex);
        output.clear();
        output.insert(output.end(), m_buffer.begin(), m_buffer.end());
        return output.size();
    }

    void push_front(const std::deque<T>& input) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_buffer.insert(m_buffer.begin(), input.begin(), input.end());
    }

    void push_front(const std::vector<T>& input) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_buffer.insert(m_buffer.begin(), input.begin(), input.end());
    }

    size_t getFromBuffer(std::vector<T>& output) {
        std::lock_guard<std::mutex> lg(m_mutex);
        output.insert(output.end(), m_buffer.begin(), m_buffer.end());
        m_buffer.clear();
        return output.size();
    }

    size_t getFromBuffer(std::deque<T>& output) {
        std::lock_guard<std::mutex> lg(m_mutex);
        output.clear();
        std::swap(output, m_buffer);
        return output.size();
    }

    bool pop_front(T& output) {
        std::lock_guard<std::mutex> lg(m_mutex);
        if (m_buffer.size() == 0)
            return false;
        output = m_buffer.front();
        m_buffer.pop_front();
        return true;
    }

    T pop_front() {
        std::lock_guard<std::mutex> lg(m_mutex);
        T out = m_buffer.front();
        m_buffer.pop_front();
        return out;
    }

    void push_back(T& input) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_buffer.push_back(input);
        if (m_buffer.size() >= m_buffer_length)
            m_buffer.pop_front();
    }

    T front() {
        std::lock_guard<std::mutex> lg(m_mutex);
        if (m_buffer.size())
            return m_buffer.front();
        return T{};
    }

    T back() {
        std::lock_guard<std::mutex> lg(m_mutex);
        if (m_buffer.size())
            return m_buffer.back();
        return T{};
    }

private:
    mutable std::mutex m_mutex;
    unsigned long m_buffer_length = 500000;
    std::deque<T> m_buffer;
};