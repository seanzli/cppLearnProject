#pragma once

struct BaseData {
    double x;
    double y;
    double z;

    BaseData() : x(0.0), y(0.0), z(0.0) {}

    BaseData(double _x, double _y, double _z) 
        : x(_x), y(_y), z(_z) {}

    BaseData operator+(const BaseData& in) {
        return BaseData(this->x + in.x, this->y + in.y, this->z + in.z);
    }

    BaseData operator-(const BaseData& in) {
        return BaseData(this->x - in.x, this->y - in.y, this->z - in.z);
    }
};

struct Point : public BaseData{

};

struct Att : public BaseData {

};

struct GpsTime {
    unsigned    sec_i;
    double      sec_f;
};

struct LidarData {
    Point   point;
    GpsTime time;
};

struct ImuData {
    Att     att;
    GpsTime time;
};