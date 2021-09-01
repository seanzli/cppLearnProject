/*
 * @Descripttion: 
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-08-25 21:13:42
 * @LastEditors: Sean
 * @LastEditTime: 2021-08-26 21:03:50
 */

#pragma once

#include <list>
#include <memory>

#include "observer.hpp"

//using pSharedPtrObs = Observer*;
using pSharedPtrObs = std::shared_ptr<Observer>;

class Subject {
public:
    virtual void attach(pSharedPtrObs) = 0;
    virtual void detach(pSharedPtrObs) = 0;
    virtual void NotifyAll() = 0;
};

class SubjectTest : public Subject{
public:
    void attach(pSharedPtrObs p_observer) {
        if (p_observer)
            m_observer_list.push_back(p_observer);
    }

    void detach(pSharedPtrObs p_observer) {
        if (p_observer == nullptr)
            return;
        m_observer_list.remove(p_observer);
    }

    void NotifyAll() {
        for (auto itr = m_observer_list.begin(); itr != m_observer_list.end(); itr++)
            (*itr)->update();
    }

private:
    std::list<pSharedPtrObs> m_observer_list;

};