#include "../include/DecodeLidarSDC.hpp"

struct SDC{
    double x, y, z;
};

DecodeSDC::DecodeSDC(const std::string& file) {
    fp = fopen(file.c_str(), "rb");
    m_buffer_size = m_buffer_size * sizeof(SDC);
    m_buffer = std::shared_ptr<char>(new char[m_buffer_size]);
}

DecodeSDC::~DecodeSDC() {
    if (fp)
        fclose(fp);
}

void convertSDC2LidarPoint(std::shared_ptr<char>& buffer, size_t size, std::vector<LidarPoint>& out) {

}

size_t DecodeSDC::getData(std::vector <LidarPoint> &out) {
    size_t size = fread(m_buffer.get(), m_buffer_size, 1, fp);
    convertSDC2LidarPoint(m_buffer, size, out);
    return size;
}