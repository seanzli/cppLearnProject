/**
 * @file singleton.cpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <iostream>
#include <thread>

class Singleton {
protected:
    Singleton(const std::string value) : m_value(value) {}
    std::string m_value;

public:
    Singleton(Singleton&) = delete;
    void operator=(const Singleton&) = delete;

    static Singleton& getInstance(const std::string& value) {
        static Singleton m_singleton(value);
        return m_singleton;
    }

    void doSomething() {}

    std::string value() const {return m_value;}
};

void thread1() {
    Singleton& singleton = Singleton::getInstance("thread1");
    std::cout << singleton.value() << "\n";
}

void thread2() {
    Singleton& singleton = Singleton::getInstance("thread2");
    std::cout << singleton.value() << "\n";
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    Singleton& singleton = Singleton::getInstance("main");
    std::cout << singleton.value() << "\n";


    t1.join();
    t2.join();

    return 0;
}