#pragma once

#include <deque>

#include "Buffer.hpp"
#include "DataSubscribe.hpp"

// decode char container
using Container = Buffer<char>;

/**
 * @brief decoder base template
 * 
 */
class BaseDecode {
public:
    BaseDecode() {}
    virtual ~BaseDecode(){}
    virtual unsigned decodeChar(Container& que) = 0;
    virtual void subscribe(std::shared_ptr<DataSubscribe> sub) = 0;
};