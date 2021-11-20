#pragma once

#include "DecoderBase.hpp"

class DecoderRtcm : public DecoderBase {

public:
    virtual void decoder(int8_t * buffer) override {}
};