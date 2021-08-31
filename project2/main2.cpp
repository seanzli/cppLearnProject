/*
 * @Author: your name
 * @Date: 2021-08-31 19:07:47
 * @LastEditTime: 2021-08-31 19:19:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /cppLearnProject/project2/main2.cpp
 */

#include <iostream>
#include <algorithm>

#include "project2.hpp"

int func(const std::string& file_path, unsigned in = 10);
int func(const std::string& file_path, unsigned in, unsigned out);

int main() {
    return 0;
}

int func(const std::string& file_path, unsigned in) {
    return func(file_path, in, in);
}

int func(const std::string& file_path, unsigned in, unsigned out) {
    
    /// check base
    if (in < 2 || 36 < in) {
        std::cout << "input base error : " << in << std::endl;
        return 4;
    }
    if (out < 2 || 36 < out) {
        std::cout << "output base error : " << out << std::endl;
        return 4;
    }

    /// init
    Project2 prj(in, out);
    std::string add1, add2;

    /// decode input file
    if (prj.decode_file(file_path, add1, add2)) {
        std::cout << "file can not open.\n";
        return 1;
    }

    std::cout << "add1 = " << add1 << std::endl;
    std::cout << "add2 = " << add2 << std::endl;

    /// check input string
    std::reverse(add1.begin(), add1.end());
    if (prj.stringValid(add1, in_base) == false) {
        std::cout << "first input number is not valid\n";
        return 2;
    }

    std::reverse(add2.begin(), add2.end());
    if (prj.stringValid(add2, in_base) == false) {
        std::cout << "second input number is not valid\n";
        return 3;
    }

    // output result
    std::string res = prj.sum(add1, add2, in_base);
    std::reverse(res.begin(), res.end());

    // change base
    prj.changeBase(res, in_base, out_base);

    std::cout << "result = " << res << ", base = " << out_base << std::endl;
    return 0;
}