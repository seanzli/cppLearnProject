#include <iostream>
#include <list>
#include <string>
#include <memory>


class IObserver {
public:
    virtual void Update(float price) = 0;
};

using ObsPtr = std::shared_ptr<IObserver>;

class ISubject {
public:
    virtual void Attach(ObsPtr) = 0;
    virtual void Detach(ObsPtr) = 0;
    virtual void Notify() = 0;
};

class ConcreteSubject : public ISubject {
public:
    ConcreteSubject() : m_fPrice(10.0) {}
    
    void SetPrice(float price) {
        m_fPrice = price;
    }

    void Attach(ObsPtr obs) {
        m_observers.push_back(obs);
    }

    void Detach(ObsPtr obs) {
        m_observers.remove(obs);
    }

    void Notify() {
        std::list<ObsPtr>::iterator itr = m_observers.begin();
        while (itr != m_observers.end()) {
            (*itr)->Update(m_fPrice);
            ++itr;
        }
    }
private:
    float m_fPrice;
    std::list<ObsPtr> m_observers;
};

class ConcreteObserver : public IObserver {
public:
    ConcreteObserver(std::string name) : m_name(name) {}
    void Update(float price) {
        std::cout << m_name << " - price : " << price << "\n";
    }
private:
    std::string m_name;

};

int main()
{
    // 创建主题、观察者
    std::shared_ptr<ConcreteSubject> pSubject(new ConcreteSubject);
    ObsPtr pObserver1(new ConcreteObserver("Jack Ma"));
    ObsPtr pObserver2(new ConcreteObserver("Pony"));

    // 注册观察者
    pSubject->Attach(pObserver1);
    pSubject->Attach(pObserver2);

    // 更改价格，并通知观察者
    pSubject->SetPrice(12.5);
    pSubject->Notify();

    // 注销观察者
    pSubject->Detach(pObserver2);
    // 再次更改状态，并通知观察者
    pSubject->SetPrice(15.0);
    pSubject->Notify();

    return 0;
}