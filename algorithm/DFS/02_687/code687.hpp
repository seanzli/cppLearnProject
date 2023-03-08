/**
 * Definition for a binary tree node.
 */
#include <iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
    int res = 1;
    int dfs(TreeNode* root, int val, int cur) {
        if (root == nullptr)
            return 0;
        int left = dfs(root->left, root->val, 1);
        int right = dfs(root->right, root->val, 1);
        res = max(res, left + right + 1);
        if (root->val == val)
            return max(left, right) + 1;
        return 0;
    }
public:
    int longestUnivaluePath(TreeNode* root) {
        if (root == nullptr)
            return 0;
        dfs(root, -1, 0);
        return res - 1;
    }
};