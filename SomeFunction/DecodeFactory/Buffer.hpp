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

    template<typename InputIterator>
    Buffer(InputIterator _first, InputIterator _last) {
        m_data = std::deque<T>(_first, _last);
    }

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

    void pop_back() {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_data.pop_back();
    }

    void pop_front() {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_data.pop_front();
    }

    void pop_front(unsigned size) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_data.erase(m_data.begin(), m_data.begin() + size);
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

    const T& operator[](unsigned int idx) {
        return m_data[idx];
    }
    
    auto begin() { return m_data.begin(); }
    auto end() {return m_data.end(); }

    template<typename InputIterator, typename DataIterator>
    void insert(DataIterator _pos, InputIterator _first, InputIterator _last) {
        m_data.insert(_pos, _first, _last);
    }

private:
    std::deque<T>   m_data;
    std::mutex      m_mutex;
};