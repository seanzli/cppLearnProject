#pragma once

#include "../include/DecodeLidarSDC.hpp"
#include "../include/generateDefine.h"

class DecodeLidar {
public:
    static DecodeLidar& getInstance() {
        static DecodeLidar m_instance;
        return m_instance;
    }
    ~DecodeLidar() = default;

    std::shared_ptr<DecodeLidarBase> getDecoder(const LidarType& type, const std::string& file) {
        switch (type) {
            case LidarType::SDC: return std::shared_ptr<DecodeSDC>(new DecodeSDC(file));
        }
        return nullptr;
    }

private:
    DecodeLidar() = default;
};