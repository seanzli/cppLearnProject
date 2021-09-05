/**
 * @file main.cpp  sample for factory pattern
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>

//------------------------------
/**
 * @brief product
 * 
 */
class Product {
public:
    virtual ~Product() {}
    virtual std::string Operation() const = 0;
};

class ConcreteProductA : public Product {
public:
    std::string Operation() const override {
        return std::string("Result of Concrete Product A\n");
    }
};

class ConcreteProductB : public Product {
public:
    std::string Operation() const override {
        return std::string("Result of Concrete Product B\n");
    }
};

//------------------------------
/**
 * @brief creator
 * 
 */

class Creator {  // creator base
public:
    virtual ~Creator() {}
    virtual Product* Factory() const = 0;

    std::string Operation() const {
        Product* p = this->Factory();
        std::string res = p->Operation();
        delete p;
        return res;
    }
};

class ConcreateCreatorA : public Creator {
public:
    Product* Factory() const override {
        return new ConcreteProductA();
    }
};

class ConcreateCreatorB : public Creator {
public:
    Product* Factory() const override {
        return new ConcreteProductB();
    }
};

int main() {
    Creator* test1 = new ConcreateCreatorA();
    std::cout << "---test1---\n";
    std::cout << test1->Operation() << std::endl;
    delete test1;

    Creator* test2 = new ConcreateCreatorB();
    std::cout << "---test2---\n";
    std::cout << test2->Operation() << std::endl;
    delete test2;

    return 0;
}