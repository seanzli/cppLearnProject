/**
 * Definition for a binary tree node.
 */

#include <unordered_map>

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
    int res;
    void dfs(TreeNode* root, long cur, unordered_map<long, int>& hash, int sum) {
        if (root == nullptr)
            return;
        cur += root->val;
        if (hash.count(cur - sum) != 0)
            res += hash[cur - sum];
        ++hash[cur];
        dfs(root->left, cur, hash, sum);
        dfs(root->right, cur, hash, sum);
        --hash[cur];
        return;
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long, int> pre_sum;
        res = 0;
        dfs(root, 0, pre_sum, targetSum);
        return res;
    }
};