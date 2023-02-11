#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    vector<int> num1 = {1,1,0,0,1};
    vector<int> num2 = {13,25,32,11};
    auto out = solution.maxChunksToSorted(num1);
    std::cout << out << "\n";
    return 0;
}