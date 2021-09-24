#include <iostream>

#include "GlobalData.hpp"
#include "Collector.hpp"
#include "Calculate.hpp"
int main() {
    CollectorManager m;
    GlobalData& m_data = GlobalData::instance();

    Calculate c(m_data.lidarData(), m_data.imuData(), m_data.condition_variable());

    // data buffer  
    Velodyne __vel(m_data.condition_variable(), m_data.lidarData());
    STIM300 __stim300(m_data.condition_variable(), m_data.imuData());

    // decoder
    m.add(__vel);
    m.add(__stim300);

    // calculate
    auto th = std::thread([](Calculate& c){c.run();}, std::ref(c));
    th.join();

    m.teminate();
    return 0;
}

