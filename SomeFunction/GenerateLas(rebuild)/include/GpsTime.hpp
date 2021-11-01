#pragma once

#include <cmath>

namespace BasicStruct {
constexpr unsigned int  SECS_IN_ONE_WEEK = 604800;
constexpr unsigned int  SECS_IN_ONE_DAY  = 86400;
constexpr double        TIME_PRECISION   = 1e-9;

struct GpsTime {
    double sec_integer;
    double sec_decimal;

    GpsTime() : sec_integer(0.0), sec_decimal(0.0) {}
    GpsTime(double _integer, double _decimal) 
        : sec_integer(_integer), sec_decimal(_decimal) {}
    
    GpsTime(double sec) {
        this->sec_integer = (double)((unsigned long long)(sec));
        this->sec_decimal = sec - this->sec_integer;
    }

    GpsTime(const GpsTime&) = default;
    GpsTime(GpsTime&&) = default;

    // assignment
    GpsTime& operator= (const GpsTime& in) {
        if (&in == this)
            return *this;
        this->sec_integer = in.sec_integer;
        this->sec_decimal = in.sec_decimal;
        return *this;
    }

    GpsTime& operator= (GpsTime&& in) {
        if (&in == this)
            return *this;
        this->sec_integer = in.sec_integer;
        this->sec_decimal = in.sec_decimal;
        return *this;
    }

    // operator overload
    GpsTime operator+(const GpsTime& in) {
        return GpsTime(this->sec_integer + in.sec_integer,
                        this->sec_decimal + in.sec_decimal);
    }
    GpsTime operator-(const GpsTime& in) {
        return GpsTime(this->sec_integer - in.sec_integer,
                        this->sec_decimal - in.sec_decimal);
    }

    bool operator<(const GpsTime& in) {
        if (this->sec_integer < in.sec_integer)
            return true;
        else if (this->sec_integer > in.sec_integer)
            return false;
        return this->sec_decimal < in.sec_decimal;
    }

    bool operator>(const GpsTime& in) {
        if (this->sec_integer > in.sec_integer)
            return true;
        else if (this->sec_integer < in.sec_integer)
            return false;
        return this->sec_decimal > in.sec_decimal;
    }

    bool operator==(const GpsTime& in) {
        return (abs(this->sec_integer - in.sec_integer) < TIME_PRECISION) &&
                (abs(this->sec_decimal - in.sec_decimal) < TIME_PRECISION);
    }
};

}