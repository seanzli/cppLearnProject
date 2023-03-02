#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    vector<string> grid = {"@fedcbBCDEFaA"};
    auto out = solution.shortestPathAllKeys(grid);
    std::cout << out << "\n";
    return 0;
}