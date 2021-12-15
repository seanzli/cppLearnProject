#pragma once

#include <type_traits>
#include <memory>
#include <exception>

template<typename T>
class uVector {
    using type = T;

private:
    size_t m_size = 0;
    size_t m_capture = 0;
    T* m_data = nullptr;

public:
    uVector() = default;
    uVector(size_t _size)
        : m_size(_size)
        , m_capture(_size)
    {
        m_data = (T*)(malloc(sizeof(T) * m_capture));
        setVal(T{});
    }

    uVector(size_t _size, T&& val)
        : m_size(_size)
        , m_capture(_size)
    {
        m_data = (T*)(malloc(sizeof(T) * m_capture));
        setVal(val);
    }

    inline size_t size() const {return m_size;}
    inline bool empty() const {return m_size == 0;}

    void clear() {
        memset(m_data, 0, sizeof(T)*m_size);
    }

    T& operator[](size_t i) {
        return m_data[i];
    }

    T& operator[](size_t i) const {
        return m_data[i];
    }

    void push_back(const T& val) {
        if (m_size == m_capture) {
            getNewMemory();
            push_back(val);
        } else {
            m_data[m_size++] = val;
        }
        return;
    }
    void pop_back() {
        if (m_size == 0)
            return;
        --m_size;
    }

    T front() {
        return m_data[0];
    }

    T back() {
        return m_data[m_size - 1];
    }

    T* begin() {
        return m_data;
    }

    T* end() {
        return m_data + m_size;
    }



private:
    void setVal(const T& val) {
        for (size_t i = 0; i < m_size; ++i)
            m_data[i] = val;
    }

    void getNewMemory() {
        T* new_buffer = (T*)(malloc(m_capture * 2 * sizeof(T)));
        memcpy(new_buffer, m_data, sizeof(T) * m_size);
        delete m_data;
        m_data = new_buffer;
        m_capture = 2 * m_capture;
    }

};