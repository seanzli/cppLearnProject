#include <chrono>
#include <string>
#include <iostream>

class Timer {
public:
    Timer(const std::string& _title) : title(_title){
        start = std::chrono::system_clock::now();
    }
    ~Timer() {
        std::chrono::duration<double> dif = std::chrono::system_clock::now() - start;
        std::cout << title << " : " << dif.count() * 1000.0 << "ms\n";
    }

private:
    std::string title;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> start;
};