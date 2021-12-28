#include "usort.hpp"

#include <iostream>

int main() {
    std::vector<int> a = {5,7,19,4,6};
    auto lam = [](int a, int b) {return a < b;};
//    sort(a, lam);

    sort(a);
    for (auto& itr : a) {
        std::cout << itr << ", ";
    }
    std::cout << std::endl;

    return 0;
}