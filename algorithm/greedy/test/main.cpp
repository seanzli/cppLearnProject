#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    vector<int> num1 = {5,6,4,3,1,2};
    vector<int> num2 = {6,3,3,1,4,5,3,4,1,3,4};
    std::cout << solution.minOperations(num1,num2) << "\n";
    return 0;
}