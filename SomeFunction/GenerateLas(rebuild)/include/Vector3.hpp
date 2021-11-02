#pragma once

#include <cmath>

namespace BasicStruct {
struct vec3 {
public:
    vec3() : x(0.0), y(0.0), z(0.0) {}
    vec3(double _x, double _y, double _z) 
        : x(_x), y(_y), z(_z) {}

    ~vec3() {}

    vec3 operator+(const vec3& op) {
        return vec3(this->x + op.x, 
                    this->y + op.y,
                    this->z + op.z);
    }

    vec3 operator-(const vec3& op) {
        return vec3(this->x - op.x, 
                    this->y - op.y,
                    this->z - op.z);
    }

    double mod() {
        return sqrt(x*x + y*y + z*z);
    }

    double mod(const vec3& op) {
        return sqrt(op.x * op.x + op.y * op.y + op.z * op.z);
    }

public:
    double x;
    double y;
    double z;
};

using ECEF = vec3;
using XYZ  = vec3;
using LLA  = vec3;
using ATT  = vec3;
}
