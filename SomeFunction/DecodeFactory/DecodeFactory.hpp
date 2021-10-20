#pragma once

#include <deque>
#include <memory>

#include "DecodeBase.hpp"
#include "DecodeNovatel.hpp"

enum class DecoderType {
    NOVATEL,
    RTCMv3,
};

/**
 * @brief Factory to create Decoder pointer
 * 
 */
class Factory {
public:
    Factory() {}
    ~Factory() {}

    static std::shared_ptr<DecodeBase> getDecoder(DecoderType type) {
        switch (type)
        {
        case DecoderType::NOVATEL:
            return std::shared_ptr<DecodeNovatel>(new DecodeNovatel());
        default:
            break;
        }
        return std::shared_ptr<DecodeBase>{};
    }

};