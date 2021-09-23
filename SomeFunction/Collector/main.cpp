
// #include <chrono>

#include "Collector.hpp"

int main() {

    auto lidar = std::make_shared<LidarObserver>();

    Velodyne vel_;

    CollectorManager m;

    vel_.attach(lidar);
    
    m.add(std::move(vel_));

    return 0;
}