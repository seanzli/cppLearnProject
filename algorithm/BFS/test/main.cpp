#include <iostream>

#include "code.hpp"
int main()
{
    Solution solution;
    // vector<vector<int>> nums = {{1,6,1},{5,8,7},{1,9,1}};
    vector<string> str = {"/a","/a/b","/c/d","/c/d/e","/c/f"};
    auto out = solution.removeSubfolders(str);
    // std::cout << out << "\n";
    return 0;
}