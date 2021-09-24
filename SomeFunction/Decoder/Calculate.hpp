#pragma once

#include <memory>
#include <future>
#include <vector>

#include "Data.hpp"
#include "StructDefine.hpp"

class Calculate {
public:
    explicit Calculate(Buffer<LidarData>& _lidar,
                       Buffer<ImuData>& _imu,
                       std::condition_variable& cv)
                       : m_lidar(_lidar)
                       , m_imu(_imu)
                       , m_cv(cv) {}

    void run() {
        isrunning.store(true);
        while (isrunning.load()) {
            {
                std::unique_lock<std::mutex> lg(m_mutex);
                m_cv.wait(lg, [this]{return !isrunning.load() 
                                         || !m_lidar.empty() 
                                         || !m_imu.empty();});
            }
            if (isrunning.load() == false)
                return;
            std::vector<LidarData> _lidar = m_lidar.getData();
            m_lidar.clear();
            std::vector<ImuData> _imu = m_imu.getData();
            m_imu.clear();
            // ... Do something
        }

    }

    void terminate() {
        isrunning.store(false);
    }

// member data
private:
    std::atomic<bool> isrunning{false};
    Buffer<LidarData>& m_lidar;
    Buffer<ImuData>&   m_imu;
    std::condition_variable& m_cv;
    std::mutex  m_mutex;


// member function
private:
};