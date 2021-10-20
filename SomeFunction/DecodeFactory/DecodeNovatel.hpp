#pragma once

#include "DecodeBase.hpp"

#include "buffer.hpp"


/**
 * @brief Specific of decoder
 * 
 */
using Obs = int; // Data type = for test;
class DecodeNovatel : public DecodeBase {
public:
    void decodeChar(Container& que) {
        que.clear();
    }

    void getData(std::deque<Obs>& que) {
        m_data.swap(que);
    }
private:
    Buffer<Obs> m_data;
};