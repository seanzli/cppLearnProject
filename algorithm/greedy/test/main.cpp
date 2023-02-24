#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    vector<int> num = {1,4,0,5,8,7,6,3,2,9};
    auto out = solution.minSwapsCouples(num);
    std::cout << out << "\n";
    return 0;
}