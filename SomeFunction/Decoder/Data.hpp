#pragma once

#include <deque>
#include <list>
#include <mutex>
#include <vector>

constexpr unsigned int MAX_SIZE = 512000;

template<typename T>
class Buffer {
    using container = std::deque<T>;

public:
    Buffer(unsigned size = MAX_SIZE) {
        size = std::min(size, MAX_SIZE);
        m_capacity = size;
    }

    ~Buffer() {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_list.clear();
    }

    size_t size() {
        std::lock_guard<std::mutex> lg(m_mutex);
        return m_list.size();
    }

    void clear() {
        std::lock_guard<std::mutex> lg(m_mutex);
        return m_list.clear();
    }

    bool empty() {
        std::lock_guard<std::mutex> lg(m_mutex);
        return m_list.empty();
    }

    void push_front(const std::vector<T>& in) {
        if (in.empty()) return;
        std::lock_guard<std::mutex> lg(m_mutex);
        m_list.insert(m_list.begin(), in.begin(), in.end());
        normalization();
    }

    void push_front(const T& in) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_list.push_front(in);
        normalization();
    }

    void emplace_front(const T& in) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_list.emplace_front(in);
        normalization();
    }

    void push_back(const std::vector<T>& in) {
        if (in.empty()) return;
        std::lock_guard<std::mutex> lg(m_mutex);
        m_list.insert(m_list.end(), in.begin(), in.end());
        normalization();
    }

    void push_back(const T& in) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_list.push_back(in);
        normalization();
    }

    void emplace_back(const T& in) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_list.emplace_back(in);
        normalization();
    }

    void pop_front(unsigned num = 1) {
        if (num == 0)
            return;
        if (num > m_list.size())
            return;
        std::lock_guard<std::mutex> lg(m_mutex);
        if (num == 1)
            return m_list.pop_front();
        m_list.erase(m_list.begin(), m_list.end() + num);
    }

    void pop_back(unsigned num = 1) {
        if (num == 0)
            return;
        if (num > m_list.size())
            return;
        std::lock_guard<std::mutex> lg(m_mutex);
        if (num == 1)
            return m_list.pop_back();
        m_list.erase(m_list.end() - num, m_list.end());
    }

    void getData(std::vector<T>& out) {
        out.clear();
        std::lock_guard<std::mutex> lg(m_mutex);
        out.insert(m_list.begin(), m_list.end());
        m_list.clear();
    }

    std::vector<T> getData() {
        std::lock_guard<std::mutex> lg(m_mutex);
        return std::vector<T>(m_list.begin(), m_list.end());
    }

private:
    unsigned int    m_capacity;
    container       m_list;
    std::mutex      m_mutex;

private:
    void normalization() {
        if (m_list.size() <= m_capacity)
            return;
        m_list.erase(m_list.begin(), m_list.end() - m_capacity);
    }
};