#pragma once

#include <vector>
#include <memory>

#include "DecoderBase.hpp"
#include "DecoderNovatel.hpp"
#include "DecoderRtcm.hpp"

enum class DECODER_TYPE {
    WAIT,
    NOVATEL,
    RTCM,
    NONE,
};

class DecoderTypeStruct {
public:
    DecoderTypeStruct(const std::initializer_list<int8_t>& _header,
                      const DECODER_TYPE _type,
                      const size_t _len)
        : header(_header), type(_type), message_length(_len) {}

public:
    std::vector<int8_t> header;
    DECODER_TYPE        type;
    size_t              message_length;
};


static const std::vector<DecoderTypeStruct> g_type_list = {
    {{(int8_t)0xAA, 0x44}, DECODER_TYPE::NOVATEL, 2},
    {{(int8_t)0xD3, 0x00}, DECODER_TYPE::RTCM, 2},
};

class DecoderFactory {
public:
    DECODER_TYPE getType(int8_t* buffer, size_t size) {
        for (size_t i = 0; i < g_type_list.size(); ++i) {
            if (size > g_type_list[i].header.size() && check(buffer, g_type_list[i].header)) {
                if (size < g_type_list[i].message_length)
                    return DECODER_TYPE::WAIT;
                else
                    return g_type_list[i].type;
            }
        }
        return DECODER_TYPE::NONE;
    }

    auto getDecoder(const DECODER_TYPE& type) {
        switch (type)
        {
        case DECODER_TYPE::NOVATEL :
            return std::shared_ptr<DecoderBase>(new DecoderNovatel);
        case DECODER_TYPE::RTCM :
            return std::shared_ptr<DecoderBase>(new DecoderRtcm);
        default:
            break;
        }
        return std::shared_ptr<DecoderBase>();
    }

private:
    bool check(int8_t* buffer, const std::vector<int8_t>& header) {
        for (size_t i = 0; i < header.size(); ++i) {
            if (buffer[i] != header[i])
                return false;
        }
        return true;
    }
};