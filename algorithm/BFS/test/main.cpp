#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    // vector<vector<int>> nums = {{1,6,1},{5,8,7},{1,9,1}};
    TreeNode* str = new TreeNode(10, new TreeNode(5, new TreeNode(3), new TreeNode(2, nullptr, new TreeNode(1))), nullptr);
    auto out = solution.pathSum(str, 8);
    // std::cout << out << "\n";
    return 0;
}