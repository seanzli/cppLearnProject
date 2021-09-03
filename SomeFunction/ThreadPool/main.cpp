/**
 * @file main.cpp
 * @author Sean
 * @brief 
 * @version 0.1
 * @date 2021-09-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>

#include "threadPool.hpp"

int main() {
    ThreadPool tp;

    auto t1 = [](){printf("lambda test1\n");};
    auto t2 = [](int a){printf("lambda test2 a = %d\n", a);};
    auto t3 = [](int& a){printf("lambda test3 a = %d\n", a);};
    tp.attach(t1);
    tp.attach(t2, 2);
    int a = 3;
    tp.attach(t3, a);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}