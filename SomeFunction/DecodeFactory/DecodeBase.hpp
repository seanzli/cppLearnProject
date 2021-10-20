#pragma once

#include <deque>

#include "buffer.hpp"

using Container = std::deque<char>;

class DecodeBase {
public:
    DecodeBase() {}
    virtual ~DecodeBase() {}
    virtual void decodeChar(Container& que) = 0;
};