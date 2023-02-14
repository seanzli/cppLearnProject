#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    vector<vector<int>> sta = {{10,60},{20,30},{30,30},{60,40}};
    auto out = solution.minRefuelStops(100, 10, sta);
    std::cout << out << "\n";
    return 0;
}