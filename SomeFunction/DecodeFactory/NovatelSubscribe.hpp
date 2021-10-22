#pragma once

#include "DataSubscribe.hpp"
#include <iostream> // for test

class NovatelSubscribe : public DataSubscribe {
public:
    void getData(BascDataTopic* dataTopic) { 
        // auto buffer = dynamic_cast<DataTopic<OBS>*>(dataTopic)->getBufferReference();
        // std::cout << buffer.size() << "\n"; // for test
        std::cout << "novatel getData\n";
    }
};