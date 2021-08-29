#include <iostream>
#include <algorithm>

#include "project2.h"

int func(const std::string& file_path);
int func(const std::string& file_path, const int in_base);
int func(const std::string& file_path, const int in_base, const int out_base);

int main(int, char**) {

    func(std::string("../test.txt"));

    func(std::string("../test2.txt"), 20);

    func(std::string("../test2.txt"), 20, 10);

    return 0;
}

int func(const std::string& file_path) {
    return func(file_path, 10, 10);
}

int func(const std::string& file_path, const int in_base) {
    return func(file_path, in_base, in_base);
}

int func(const std::string& file_path, const int in_base, const int out_base) {
        // decode input file
    std::string add1, add2;
    if (decode_file(file_path, add1, add2)) {
        std::cout << "file can not open.\n";
        return 1;
    }

    // check input validable
    std::reverse(add1.begin(), add1.end());
    if (stringValid(add1, in_base, false) == false) {
        std::cout << "first input number is not valid\n";
        return 2;
    }
    
    std::reverse(add2.begin(), add2.end());
    if (stringValid(add2, in_base) == false) {
        std::cout << "second input number is not valid\n";
        return 3;
    }

    // output result
    std::string res = sum(add1, add2, in_base);
    std::reverse(res.begin(), res.end());

    // change base
    changeBase(res, in_base, out_base);

    // output
    std::reverse(add1.begin(), add1.end());
    std::reverse(add2.begin(), add2.end());
    std::cout << "Add num1 = " << add1 << ", base = " << in_base << "\n";
    std::cout << "Add num2 = " << add2 << ", base = " << in_base << "\n";
    std::cout << "result = " << res << ", base = " << out_base << std::endl;
    return 0;
}
