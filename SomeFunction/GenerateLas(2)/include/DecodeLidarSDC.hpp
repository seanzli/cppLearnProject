#pragma once

#include "DecodeLidarBase.hpp"
#include <memory>

class DecodeSDC : public DecodeLidarBase {
public:
    explicit DecodeSDC(const std::string& file);
    ~DecodeSDC();
    virtual size_t getData(std::vector<LidarPoint>& out) override;

private:
    FILE                  *fp = nullptr;
    size_t                m_buffer_size = 1024;
    std::shared_ptr<char> m_buffer;
};