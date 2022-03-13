#pragma once

#include <string>
#include <atomic>
#include <thread>
#include <condition_variable>

#include "../include/generateDefine.h"

struct GeneratePara{
    std::string imu_path;
    std::string gnss_path;
    std::string lidar_path;
    int imu_type;
    LidarType lidar_type;
    std::string las_path;
};

class GenerateLas {
public:
    explicit GenerateLas(const GeneratePara& para) : m_para(para) {}
    ~GenerateLas() = default;
    void run();
    void terminate() {
        m_running.store(false);
        if (m_process.joinable())
            m_process.join();
    }
private:
    std::thread             m_process;
    std::atomic<bool>       m_running{false};
    std::condition_variable m_cv;
    std::mutex              m_mutex;
    GeneratePara            m_para;
};