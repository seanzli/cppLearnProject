#pragma once

#include <type_traits>
#include <memory>
#include <exception>

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

    vector& operator=(const vector& rhs) {
        if (&rhs == this)
            return *this;
        do_destroy(this->m_size,this->m_data);
        m_size = 0;
        m_capacity = rhs.m_capacity;
        m_data = static_cast<ValueT*>(operator new(
                rhs.m_capacity * sizeof(ValueT)
                ));
        try {
            for (size_type i = 0; i < rhs.m_size; ++i) {
                ::new(&m_data[i]) ValueT(rhs.m_data[i]);
                ++m_size;
            }
        } catch(...) {
            do_destroy(m_size, m_data);
            throw;
        }
        return *this;
    }
    vector& operator=(vector&& rhs) noexcept {
        if (&rhs == this)
            return *this;
        this->m_data = rhs.m_data;
        this->m_size = rhs.m_size;
        this->m_capacity = rhs.m_capacity;

        rhs.m_data = nullptr;
        rhs.m_size = 0;
        rhs.m_capacity = 0;
        return *this;
    }

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
        /// delete all element
        for (size_type i = 0; i < size; ++i) {
            ptr[i].~ValueT();
        }
        if (ptr)
            ::operator delete(ptr);
    }
};
}