/**
 * @file builder.cpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// #include <string>

// class Person {
// public:
//     std::string name, address;
//     std::string company, company_name;
// };


// class PersonBuilderBase {
//     Person &person;
// public:
//     explicit PersonBuilderBase(Persion _p) : person{_p} {}

//     operator Person() {
//         return std::move(person);
//     }
// };

// class PersonBuilder : public PersonBuilderBase {
//     Person p;
// public:
//     PersonBuilder() : PersonBuilderBase{p} {}
// };

// class PersonAddressBuilder : public PersonBuilderBase {
//     using self = PersonAddressBuilder;
// public:
//     explicit PersonAddressBuilder(Person &per)
//         : PersonBuilderBase{per} {}
    
//     self& at(std::string address) {
//         person.address = address;
//         return *this;
//     }

//     self& name(std::string name) {
//         person.name = name;
//         return *this;
//     }
// }

// class PersonJobBuilder : public PersonBuilderBase {
//     using self = PersonJobBuilder;
// public:
//     explicit PersonJobBuilder(Person &per)
//         : PersonJobBuilder{per} {}
    
//     self& at(std::string company) {
//         person.company = company;
//         return *this;
//     }

//     self& name(std::string company_name) {
//         person.company_name = company_name;
//         return *this;
//     }
// }

// int main() {
    
// }

//--------------------------------------------------------------------------
#include <string>
#include <vector>

using namespace std;

class Product {
private:
    string m_partA, m_partB, m_partC;
public:
    Product();
    ~Product();
    void setPartA(const string& s) {
        m_partA = s;
    }
    void setPartB(const string& s) {
        m_partB = s;
    }
    void setPartC(const string& s) {
        m_partC = s;
    }
}

class Builder {
public:
    virtual ~Builder(){};
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    virtual void BuildPartC() = 0;
    virtual Product* GetProduct() = 0;
};

class ConcreteBuilder1 : public Builder {
public:
    ConcreteBuilder1() {
        this->m_pProduct = new Product();
        cout << "Creat empty product\n";
    }
    ~ConcreteBuilder1() {
        delete this->m_pProduct;
        this->m_pProduct = nullptr;
    }
    virtual void BuildPartA() override {
        this->m_pProduct->setPartA("A");
    }
    virtual void BuildPartB() override {
        this->m_pProduct->setPartA("B");
    }
    virtual void BuildPartC() override {
        this->m_pProduct->setPartA("C");
    }
    virtual Product* GetProduct() override {
        return this->m_pProduct;
    }
private:
    Product* m_pProduct;
};

class ConcreteBuilder2 : public Builder {
public:
    ConcreteBuilder2();
    ~ConcreteBuilder2();
    virtual void BuildPartA() override;
    virtual void BuildPartB() override;
    virtual void BuildPartC() override;
    virtual Product* GetProduct() override;
private:
    Product* m_pProduct;
};

class Director {
public:
    Director(Builder* pBuilder) {
        this->m_pBuilder = pBuilder;
    }
    ~Director() {
        delete this->m_pBuilder;
        this->m_pBuilder = nullptr;
    }

    void Construct() {
        this->m_pBuilder->BuildPartA();
        this->m_pBuilder->BuildPartB();
        this->m_pBuilder->BuildPartC();
    }
private:
    Builder* m_pBuilder;
};

int main() {
    Director * pDirector = new Director(new ConcreteBuilder1());
    pDirector->Construct();
}