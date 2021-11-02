#include <iostream>

#include "Vector3.hpp"

using namespace BasicStruct;

int main() {
    ATT a{};
    std::cout << a.x << ' ' << a.y << ' ' << a.mod() << std::endl;
}