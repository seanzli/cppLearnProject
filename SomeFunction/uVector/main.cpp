#include "uVector.hpp"

#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& os, uVector<T>& op) {
    for (size_t i = 0; i < op.size(); ++i) {
        os << op[i] << ", ";
    }
    os << "\n";
    return os;
}

int main() {
    uVector<double> a;
    std::cout << a;

    uVector<double> b(3);
    std::cout << b;

    uVector<double> c(3, 4.2);
    std::cout << c;

    c.push_back(4.3);
    std::cout << c;
}

