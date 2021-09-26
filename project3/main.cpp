/**
 * @file main.cpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>

#include "readSudo.hpp"

int main() {
    readSudo reader(std::string("../sudo/easy.txt"));

    auto& data = reader.getData();

    std::cout << "data.size() = " << data.size() << std::endl;
    for (auto& i : data) {
        for (auto& j : i) {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }

    return 0;
}