/**
 * @file Proxy.cpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>

class Subject {
public:
    virtual void Request() const = 0;
};

class RealSubject : public Subject {
public:
    void Request() const override {
        std::cout << "RealSubject: Handling request\n";
    }
};

class Proxy : public Subject {
private:
    RealSubject* real_subject_;

    bool CheckAccess() const {
        std::cout << "Proxy: Check access prior to firing a real request.\n";
        return true;
    }

    void LogAccess() const {
        std::cout << "Proxy: Logging the time of request.\n";
    }

public:
    Proxy(RealSubject *real) : real_subject_(new RealSubject(*real)) {}
    ~Proxy() {
        delete real_subject_;
    }

    void Request() const override {
        if (CheckAccess()) {
            this->real_subject_->Request();
            this->LogAccess();
        }
    }
};

void ClientCode(const Subject &subject) {
    subject.Request();
}

int main() {
    std::cout << "Client: Executing the client code with a real subject:\n";
    RealSubject *real_subject = new RealSubject;
    ClientCode(*real_subject);
    std::cout << "\n";
    std::cout << "Client: Executing the same client code with a proxy:\n";
    Proxy *proxy = new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;
    return 0;
}