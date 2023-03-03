/**
 * Definition for a binary tree node.
 */
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == nullptr)
            return res;
        queue<TreeNode*> que;
        que.push(root);
        bool turn = false;
        while (que.size()) {
            vector<int> cur;
            int n = que.size();
            for (int i = 0; i < n; i++) {
                TreeNode* node = que.front(); que.pop();
                cur.push_back(node->val);
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
            if (turn)
                reverse(cur.begin(), cur.end());
            turn = !turn;
            
            res.push_back(cur);
        }
        return res;
    }
};