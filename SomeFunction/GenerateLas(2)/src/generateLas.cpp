#include "../include/generateLas.hpp"

#include <vector>

#include "../include/DecoderLidarFileFactory.hpp"

// need to complete
class Pos;
std::vector<Pos> calculatePos(const std::string& imu_path, int imu_type, const std::string& gnss_path) {
    return std::vector<Pos>();
}


void GenerateLas::run() {
    std::vector<Pos> pos = calculatePos(m_para.imu_path, m_para.imu_type, m_para.gnss_path);
    auto decoder = DecodeLidar::getInstance().getDecoder(m_para.lidar_type, m_para.lidar_path);

    // auto generate =

}