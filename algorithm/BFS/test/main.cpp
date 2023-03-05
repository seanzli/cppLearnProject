#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    vector<vector<int>> edge = {{1,2}};
    auto out = solution.secondMinimum(2, edge, 3, 2);
    std::cout << out << "\n";
    return 0;
}