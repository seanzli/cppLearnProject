#pragma once

#include <vector>
#include <string>

struct LidarPoint {
    double x, y, z;
    int return_num, return_sum;
};

class DecodeLidarBase {
public:
    virtual ~DecodeLidarBase() = default;
    virtual size_t getData(std::vector<LidarPoint>& points) = 0;
};