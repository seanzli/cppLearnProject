#pragma once

#include <deque>

#include "buffer.hpp"

// decode char container
using Container = std::deque<char>;

/**
 * @brief decoder base template
 * 
 */
class DecodeBase {
public:
    DecodeBase() {}
    virtual ~DecodeBase() {}
    virtual void decodeChar(Container& que) = 0;
};