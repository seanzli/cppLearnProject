#include "MultiThreadFor.hpp"
#include "../Timer/Timer.hpp"

int main() {
    ThreadFor p;

    size_t count = 100000;
    std::vector<int> add1(count, 1);
    std::vector<int> add2(count, 2);
    std::vector<int> out(count);

    auto fun = [](const int& a, const int& b) {return a + b;};
    // test1
    {
        Timer tp("normal");
        p.run(fun, count, out.begin(), add1.begin(), add2.begin());
    }

    {
        Timer tp("cv");
        p.run_cv(fun, count, out.begin(), add1.begin(), add2.begin());
    }

    {
        Timer tp("mutex");
        p.run_mutex(fun, count, out.begin(), add1.begin(), add2.begin());
    }
}