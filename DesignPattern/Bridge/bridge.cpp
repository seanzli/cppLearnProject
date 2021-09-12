/**
 * @file bridge.cpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>

class Implementation {
public:
    virtual ~Implementation() {}
    virtual std::string OperationImplementation() const = 0;
};

class ConcreteImplementationA: public Implementation {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationA\n";
    }
};

class ConcreteImplementationB: public Implementation {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationB\n";
    }
};


class Abstraction {
protected:
    Implementation* m_Implementation;
public:
    Abstraction(Implementation* _imp) : m_Implementation(_imp) {}
    virtual ~Abstraction() {}

    virtual std::string Operation() const {
        return "Abstraction: Base operation with: \n" 
            + m_Implementation->OperationImplementation();
    }
};

class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(Implementation* _imp) : Abstraction(_imp) {}
    std::string Operation() const override {
        return "ExtendedAbstraction: Expand operation with: \n" 
            + m_Implementation->OperationImplementation();
    }
};

void ClientCode(const Abstraction& abstraction) {
    std::cout << abstraction.Operation();
}
/**
 * The client code should be able to work with any pre-configured abstraction-
 * implementation combination.
 */

int main() {
    Implementation* implementation = new ConcreteImplementationA;
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    std::cout << std::endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;

    return 0;
}