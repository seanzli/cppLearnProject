#pragma once

#include "DecodeBase.hpp"

#include "buffer.hpp"

using Obs = int; // for test;

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