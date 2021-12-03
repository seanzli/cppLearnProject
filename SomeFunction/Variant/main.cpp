#include "VariantT.hpp"

#include <iostream>

int main() {
    VariantT<int, double> val = 1, val2(2.10);
    std::cout << val.Get<int>() << std::endl;
    std::cout << val2.Get<double>() << std::endl;

}