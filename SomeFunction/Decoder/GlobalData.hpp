#pragma once

#include <future>

#include "StructDefine.hpp"
#include "Data.hpp"


class GlobalData {
public:
    static GlobalData& instance() {
        static GlobalData m_globalData;
        return m_globalData;
    }
    ~GlobalData() {}

    Buffer<LidarData>& lidarData() {return lidar_data;}
    Buffer<ImuData>&   imuData() {return imu_data;}
    std::condition_variable& condition_variable() {return m_cv;}
    // std::mutex& mutex() {return m_mutex;}

private:
    GlobalData() {}

    Buffer<LidarData> lidar_data;
    Buffer<ImuData> imu_data;

    mutable std::condition_variable m_cv;
    // mutable std::mutex              m_mutex;
};