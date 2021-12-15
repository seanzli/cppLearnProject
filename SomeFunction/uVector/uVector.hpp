#pragma once

#include <type_traits>
#include <memory>
#include <exception>

template<typename T>
class uVector {
    using type = T;

private:
    size_t m_size = 0;
    size_t m_capacity = 0;
    T* m_data = nullptr;

public:
    uVector() = default;
    uVector(size_t _size)
        : m_size(_size)
        , m_capacity(_size)
    {
        m_data = (T*)(malloc(sizeof(T) * m_capacity));
        setVal(T{});
    }

    uVector(size_t _size, T&& val)
        : m_size(_size)
        , m_capacity(_size)
    {
        m_data = (T*)(malloc(sizeof(T) * m_capacity));
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
        if (m_size == m_capacity) {
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
        T* new_buffer = (T*)(malloc(m_capacity * 2 * sizeof(T)));
        memcpy(new_buffer, m_data, sizeof(T) * m_size);
        delete m_data;
        m_data = new_buffer;
        m_capacity = 2 * m_capacity;
    }
};

namespace my {
template <typename ValueT>
class vector {
public:
    using value_type        = ValueT;
    using reference_type    = ValueT&;
    using const_reference   = const ValueT&;
    using iterator          = ValueT*;
    using const_iterator    = const ValueT*;

    using size_type         = ::size_t ;
    using difference_type   = ::ptrdiff_t ;

private:
    ValueT*     m_data;
    size_type   m_size;
    size_type   m_capacity;

public:
    constexpr vector() noexcept
        : m_data(), m_size(), m_capacity()
    {}

    ~vector() {
        /// delete all element
        this->do_destroy(m_size, m_data);
    }

    vector(const vector& rhs) {
        this->m_data = static_cast<ValueT*>(operator new(
                rhs.m_capacity * sizeof(ValueT)
                ));
        this->m_size = 0;
        this->m_capacity = rhs.m_capacity;
        /// constructor all element
        try {
            for (size_type i = 0; i < rhs.m_size; ++i) {
                ::new(&this->m_data[i]) ValueT(rhs.m_data[i]);
                ++this->m_size;
            }
        } catch(...) { /// if new element throw exception
            do_destroy(m_size, m_data);
            throw;
        }
    }

    vector(vector&& rhs) noexcept {
        this->m_data = rhs.m_data;
        this->m_size = rhs.m_size;
        this->m_capacity = rhs.m_capacity;

        rhs.m_data = nullptr;
        rhs.m_size = 0;
        rhs.m_capacity = 0;
    }
//    /// TODO
    vector& operator=(const vector& rhs) {}
    vector& operator=(vector&& rhs) noexcept {}

public:
    iterator begin() noexcept {
        return this->m_data;
    }

    const_iterator begin() const noexcept {
        return this->m_data;
    }

    iterator end() noexcept {
        return this->m_data + this->m_size;
    }

    const_iterator end() const noexcept {
        return this->m_data + this->m_size;
    }

    value_type* data() noexcept {
        return this->m_data;
    }

    const value_type* data() const noexcept {
        return this->m_data;
    }

    size_type size() const noexcept {return this->m_size;}
    size_type capacity() const noexcept {return this->m_capacity;}
    bool empty() const noexcept {return this->m_size == 0;}

    /// modify
    void clear() const noexcept {
        for (size_type i = 0; i < this->m_size; ++i)
            this->m_data[i].~ValueT();
    }

    void pop_back() noexcept {
        assert(!this->empty());
        size_type k = this->m_size - 1;
        this->m_data[k].~ValueT();
        this->m_size = k;
    }

    void push_back(const ValueT& value) {
        this->emplace_back(value);
    }

    void push_back(ValueT&& value) {
        this->emplace_back(std::move(value));
    }

    template<typename...ArgsT>
    reference_type emplace_back(ArgsT&&... args) {
        if (this->m_size < this->m_capacity) {
            /// memory is enough, m_data[m_size] can not be nullptr
            size_type k = this->m_size;
            ::new(&this->m_data[k]) ValueT(::std::forward<ArgsT>(args)...);
            ++this->m_size;
            return this->m_data[k];
        }

        /// memory is not enough, need to allocate more memory
        size_type new_capacity = this->m_size + 2;
        new_capacity |= this->m_size / 2; /// * 1.5

        size_type new_size = 0;

        auto new_data = static_cast<ValueT*>(
                operator new(new_capacity * sizeof(ValueT))
                );

        try {
            for (size_type i = 0; i < this->m_size; ++i) {
                ::new(&new_data[i]) ValueT(std::move(this->m_data[i]));
                ++new_size;
            }
            ::new(&new_data[new_size]) ValueT(::std::forward<ArgsT>(args)...);
            ++new_size;
        } catch (...) {
            do_destroy(new_size, new_data);
            throw;
        }

        for (size_type i = 0; i < this->m_size; ++i)
            this->m_data[i].~ValueT();
        if (this->m_data)
            operator delete(this->m_data);
        this->m_data = new_data;
        this->m_size = new_size;
        this->m_capacity = new_capacity;

        return this->m_data[new_size];
    }

private:
    void do_destroy(size_type size, ValueT* ptr) noexcept {
        for (size_type i = 0; i < size; ++i) {
            ptr[i].~ValueT();
        }
        if (ptr)
            ::operator delete(ptr);
    }
};
}