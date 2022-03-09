#include "memoryPool.hpp"

#include <iostream>

using namespace std;



class ActualClass {
    static int count;
    int No;
public:
    ActualClass() {
        No = count;
        count++;
    }

    void print() {
        cout << this << " " << "the " << No << " object\n";
    }

    void* operator new(size_t size);
    void operator delete(void* p);
};

MemPool<sizeof(ActualClass), 2> mp;

void* ActualClass::operator new(size_t size) {
    return mp.malloc();
}

void ActualClass::operator delete(void *p) {
    return mp.free(p);
}

int ActualClass::count = 0;

int main() {
    ActualClass* p1 = nullptr;

    p1 = new ActualClass;
    p1->print();

    ActualClass* p2 = nullptr;
    p2 = new ActualClass;
    p2->print();

    delete p1;
    p1 = new ActualClass;
    p1->print();

    ActualClass* p3 = nullptr;
    p3 = new ActualClass;
    p3->print();

    delete p1;
    delete p2;
    delete p3;

    getchar();
}