/*
 * @Descripttion: 
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-25 21:06:44
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-26 21:06:24
 */
#include <iostream>

#include "./include/subscribe.hpp"

int main(int, char**) {
    SubjectTest sub;

    sub.attach(std::shared_ptr<Observer>(new ObserverTest));
    sub.NotifyAll();

    return 1;
}
