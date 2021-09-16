/**
 * @file Facade.cpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <iostream>

class Subsystem1 {
public:
    std::string Operation1() const {
        return "SubSystem1: ready\n";
    }
    std::string OperationN() const {
        return "SubSystem1: Go\n";
    }
};

class Subsystem2 {
public:
    std::string Operation1() const {
        return "SubSystem2: Get ready\n";
    }
    std::string OperationZ() const {
        return "SubSystem2: Go\n";
    }
};

class Facade {
protected:
    Subsystem1* subsystem1_;
    Subsystem2* subsystem2_;
public:
    Facade(Subsystem1* sub1_ = nullptr,
           Subsystem2* sub2_ = nullptr) {
        subsystem1_ = sub1_ ? : new Subsystem1();
        subsystem2_ = sub2_ ? : new Subsystem2();
    }
    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
    }

    std::string Operation() {
        std::string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }
};

void ClientCode(Facade *facade) {
    std::cout << facade->Operation();
}

int main() {
    Subsystem1 *subsystem1 = new Subsystem1;
    Subsystem2 *subsystem2 = new Subsystem2;
    Facade *facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);

    delete facade;

    return 0;
}