#include "uVector.hpp"

#include <string>
#include <iostream>

struct str {
    double  m_data;
public:
    str() = default;
    ~str() = default;
};

int main() {
    my::vector<std::string> a;
    a.push_back("hello");
    a.emplace_back();
    a.emplace_back("hello", 3);

    my::vector<std::string> b;
    b = std::move(a);
    std::cout << "b\n";
    for (auto& str : b) {
        std::cout << str << std::endl;
    }
    std::cout << "a\n";
    for (auto& str : a) {
        std::cout << str << std::endl;
    }
    return 0;
}

