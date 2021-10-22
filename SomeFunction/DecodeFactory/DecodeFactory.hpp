#pragma once

#include <deque>
#include <memory>

#include "DecodeNovatel.hpp"

enum class DecoderType {
    WAIT,
    NOT_FIND,
    NOVATEL,
    RTCMv3,
    VELODYNE,
};

/**
 * @brief Factory to create Decoder pointer
 * 
 */
class Factory {
public:
    Factory(){}
    ~Factory(){}

    std::shared_ptr<BaseDecode> getDecoder(const DecoderType& type) {
        switch (type)
        {
        case DecoderType::NOVATEL: 
            if (!p_novatel_decoder) {
                p_novatel_decoder = \
                    std::shared_ptr<NovatelDecoder>(new NovatelDecoder());
            }
            return p_novatel_decoder;
        }
        return std::shared_ptr<BaseDecode>{};
    }

    void attach(const DecoderType& type, std::shared_ptr<DataSubscribe> sub) {
        auto decoder = getDecoder(type);
        if (!decoder)
            return;
        decoder->subscribe(sub);
    }

private:
    std::shared_ptr<NovatelDecoder> p_novatel_decoder;
};

class Decoder {
public:
    Decoder() {}
    void decode(char* buffer, unsigned int size) {
        Container que(buffer, buffer + size);
        decode(que);
    }

    void attach(const DecoderType& type, std::shared_ptr<DataSubscribe> sub) {
        m_factory.attach(type, sub);
    }

    void decode(Container& que) {
        unsigned size = 0;
        while (!que.empty()) {
            auto type = contextType(que);
            switch (type)
            {
            case DecoderType::NOT_FIND:
                size = 1;
                break;
            case DecoderType::NOVATEL:
                size = m_factory.getDecoder(type)->decodeChar(que);
                break;
            default:
                size = 1;
                break;
            }
            que.pop_front(size);
        }
    }

private:
    DecoderType contextType(Container& que) {
        if (que.empty())
            return DecoderType::WAIT;
        if (isNovatel(que))
            return DecoderType::NOVATEL;
        
        return DecoderType::NOT_FIND;
    }

    bool isNovatel(Container& que) {
        if (que.size() < 2)
            return false;
        if (que[0] == (char)(0xAA) && que[1] == (char)(0x44))
            return true;
        return false;
    }

private:
    Factory                 m_factory;
};