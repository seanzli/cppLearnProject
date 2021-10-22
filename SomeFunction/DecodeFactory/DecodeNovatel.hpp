#pragma once

#include "DecodeBase.hpp"

/**
 * @brief Specific of decoder
 * 
 */
using OBS = int; // Data type = for test;

class NovatelDecoder : public BaseDecode {
public:
    virtual ~NovatelDecoder(){}
    virtual unsigned decodeChar(Container& que) {
        m_data.notify();
        return 1;
    }

    virtual void subscribe(std::shared_ptr<DataSubscribe> sub) {
        m_data.attach(sub);
    }

private:
    DataTopic<OBS> m_data;
};