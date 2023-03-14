#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    // vector<vector<int>> nums = {{1,6,1},{5,8,7},{1,9,1}};
    TreeNode* str = new TreeNode(3, new TreeNode(9, nullptr, nullptr), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    auto out = solution.verticalTraversal(str);
    // std::cout << out << "\n";
    return 0;
}