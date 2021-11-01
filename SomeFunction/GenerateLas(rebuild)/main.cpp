#include <iostream>

#include "GpsTime.hpp"

using namespace BasicStruct;

int main() {
    GpsTime t1(1,2);
    GpsTime t2(1,2);
    
    std::cout << (t1 == t2) << std::endl;
}