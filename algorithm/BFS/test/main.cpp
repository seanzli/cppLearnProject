#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    vector<int> nums = {3,1,4,2};
    auto out = solution.minSubarray(nums, 6);
    std::cout << out << "\n";
    return 0;
}