#pragma once

#include <memory>

class DecoderBase {
public:
    virtual ~DecoderBase(){}

    virtual void decoder(int8_t* buffer) = 0;
};