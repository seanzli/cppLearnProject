#pragma once

#include "DecoderBase.hpp"

class DecoderNovatel : public DecoderBase {

public:
    virtual void decoder(int8_t * buffer) override {}
};