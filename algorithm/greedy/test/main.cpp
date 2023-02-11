#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    vector<int> num1 = {12,24,8,32};
    vector<int> num2 = {13,25,32,11};
    auto out = solution.advantageCount(num1,num2);
    for (const auto& itr : out) {
        std::cout << itr << ",";
    }
    return 0;
}