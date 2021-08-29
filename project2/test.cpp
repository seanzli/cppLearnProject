#include <iostream>
#include <algorithm>

#include "project2.h"

int main() {
    
    int a = -98, b = 19;
    std::string str1 = std::to_string(a); std::reverse(str1.begin(), str1.end());
    std::string str2 = std::to_string(b); std::reverse(str2.begin(), str2.end());
    std::string out = sum(str1, str2, 10); 
    std::reverse(out.begin(), out.end());

    // input base = 10
    for (int a = -100; a < 100; a++) {
        for (int b = -100; b < 100; b++) {
            std::string str1 = std::to_string(a); std::reverse(str1.begin(), str1.end());
            std::string str2 = std::to_string(b); std::reverse(str2.begin(), str2.end());
            std::string out = sum(str1, str2, 10); std::reverse(out.begin(), out.end());
            if (out != std::to_string(a+b)) {
                std::cout << "a = " << a << " , b = " << b << " out = " << out << " true = " << std::to_string(a+b) << "\n";
                return 0;
            }
        }
    }

    // base change
    std::string in = "5hd4";
    changeBase(in, 28, 36);
    std::cout << in << std::endl;

    return 1;
    
}