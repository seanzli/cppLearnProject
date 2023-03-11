#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    vector<vector<int>> nums = {{1,6,1},{5,8,7},{1,9,1}};
    auto out = solution.getMaximumGold(nums);
    std::cout << out << "\n";
    return 0;
}