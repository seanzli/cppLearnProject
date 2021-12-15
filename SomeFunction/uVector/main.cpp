#include "uVector.hpp"

#include <string>
#include <iostream>


int main() {
    my::vector<std::string> a;
    a.push_back("hello");
    a.emplace_back();
    a.emplace_back("hello", 3);

    for (const auto& str : a) {
        std::cout << str << std::endl;
    }
}

