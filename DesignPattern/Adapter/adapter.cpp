/**
 * @file adapter.cpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>
#include <algorithm>


class Target {
public:
    virtual ~Target() = default;

    virtual std::string Request() const {
        return "Target: Default target's behavior.\n";
    }
};

class Adaptee {
public:
    std::string SpecificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

class Adapter : public Target {
private:
    Adaptee* m_adaptee;
public:
    Adapter(Adaptee* adaptee) : m_adaptee(adaptee) {}
    std::string Request() const override {
        std::string to_reverse = this->m_adaptee->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

void ClientCode(const Target* target) {
    std::cout << target->Request();
}

int main () {
    std::cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    ClientCode(target);
    std::cout << "\n\n";
    Adaptee *adaptee = new Adaptee;
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the Adapter:\n";
    Adapter *adapter = new Adapter(adaptee);
    ClientCode(adapter);
    std::cout << "\n";

    delete target;
    delete adaptee;
    delete adapter;

    return 0;
}