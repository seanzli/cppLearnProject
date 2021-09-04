#include "CommandWithThreadPool.hpp"

#include <iostream>

using namespace CommandSystem;

void func1() {
    printf("---\nno argument, void output\n");
}

void func2(int a) {
    std::cout << "---\none argument input test.\n";
    std::cout << "int argument a = " << a << "\n";
}

void func3(int a, int b) {
    std::cout << "---\ntwo argument input test.\n";
    std::cout << "int argument a = " << a << "\n";
    std::cout << "int argument b = " << b << "\n";
}

int func4(int a, double b) {
    std::cout << "---\ntwo argument input, int output test.\n";
    std::cout << "int argument a = " << a << "\n";
    std::cout << "int argument b = " << b << "\n";
}

struct FuncTest {
    int a;
    double b;
};

void func5(int a, FuncTest t) {
    std::cout << "---\nStruct argument test\n";
    std::cout << "int a = " << a << "\n";
    std::cout << "struct t.a = " << t.a << "\n";
    std::cout << "struct t.b = " << t.b << "\n";
}

void func6(int a, FuncTest& t) {
    std::cout << "---\nStruct reference argument test\n";
    std::cout << "int a = " << a << "\n";
    std::cout << "struct t.a = " << t.a << "\n";
    std::cout << "struct t.b = " << t.b << "\n";
}

int main() {
    ManagerTP m(2);

    m.attach("func1", Command<>(func1));
    m.attach("func2", Command<int>(func2));
    m.attach("func3", Command<int, int>(func3));
    m.attach("func4", Command<int, int>(func4));
    m.attach("func5", Command<int, FuncTest>(func5));
    m.attach("func6", Command<int, FuncTest&>(func6));



    // lambda
    m.attach("func7", Command<>([](){printf("---\nLambda \n");}));
    m.attach("func8", Command<int>([](int i){
        printf("---\nLambda a = %d \n", i);}));

std::cout << "-----------------------start execute\n";
    m.execute("func1");
    m.execute("func2", 1);
    m.execute("func3", 1, 2);
    m.execute("func4", 1, 2);
    FuncTest f{4,5};
    m.execute("func5", 1, f);
    m.execute("func6", 1, f);
    m.execute("func7");
    m.execute("func8", 30);

    std::this_thread::sleep_for(std::chrono::seconds(8));

}