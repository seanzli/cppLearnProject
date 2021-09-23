#pragma once

#include <iostream>

class Observer {
public:
    virtual ~Observer() {}
    virtual void update() = 0;
};

class LidarObserver : public Observer {
public:
    void update() override {
        std::cout << "lidar observer: update\n";
        return;
    }
};