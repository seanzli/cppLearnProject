/*
 * @Author: Sean
 * @Date: 2021-08-25 21:08:13
 * @LastEditTime: 2021-08-25 21:31:45
 * @LastEditors: Sean
 * @Description: observer
 * @FilePath: /DataSubscribe/include/observer.hpp
 */

#pragma once
#include <vector>
#include <iostream>

class Observer {
public:
    virtual ~Observer() {}
    virtual void update() = 0;

};

class ObserverTest : public Observer {
public:
    void update() {
        std::cout << "Observer\n" << std::endl;
    }
};