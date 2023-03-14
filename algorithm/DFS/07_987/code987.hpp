#include <map>
#include <vector>
#include <algorithm>

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
    map<int, map<int, vector<int>>> hash; // col -> (row, vec(val))
    void dfs(TreeNode* root, int row, int col) {
        if (root == nullptr)
            return;
        hash[col][row].push_back(root->val);
        dfs(root->left, row + 1, col - 1);
        dfs(root->right, row + 1, col + 1);
        return;
    }
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        dfs(root, 0, 0);
        vector<vector<int>> res;
        for (auto& itr1 : hash) {
            vector<int> c;
            for (auto& itr2 : itr1.second) {
                auto& v = itr2.second;
                sort(v.begin(), v.end());
                c.insert(c.end(), v.begin(), v.end());
            }
            res.push_back(c);
        }
        return res;
    }
};