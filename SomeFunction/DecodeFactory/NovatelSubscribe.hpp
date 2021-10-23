#pragma once

#include "DataSubscribe.hpp"
#include <iostream> // for test

class NovatelSubscribe : public DataSubscribe {
public:
    void getData(BascDataTopic* dataTopic) { 

        auto topic = dynamic_cast<DataTopic<OBS>*>(dataTopic);
        topic->getBufferReference().push_back(OBS{});
    }
};