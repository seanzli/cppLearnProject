#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    vector<int> num = {5,2,4,6,6,3};
    vector<vector<int>> que = {{12,4},{8,1},{6,3}};
    auto out = solution.maximizeXor(num, que);
    for (auto itr : out) {
        std::cout << itr << "\n";
    }
    return 0;
}