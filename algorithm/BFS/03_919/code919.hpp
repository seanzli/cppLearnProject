/**
 * Definition for a binary tree node.
 */
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class CBTInserter {
    TreeNode* m_root = nullptr;
    queue<TreeNode*> m_next;
public:
    CBTInserter(TreeNode* root) {
        m_root = root;
        queue<TreeNode*> que;
        if (root) {
            que.push(root);
        }
        while (!que.empty()) {
            int n = que.size();
            for (int i = 0; i < n; ++i) {
                TreeNode* cur = que.front(); que.pop();
                if (cur->left)
                    que.push(cur->left);
                if (cur->right)
                    que.push(cur->right);
                if (cur->right == nullptr)
                    m_next.push(cur);
            }
        }
    }
    int insert(int val) {
        TreeNode* node = new TreeNode(val);
        m_next.push(node);
        TreeNode* n = m_next.front();
        if (n->left == nullptr)
            n->left = node;
        else {
            n->right = node;
            m_next.pop();
        }
        return n->val;
    }
    
    TreeNode* get_root() {
        return m_root;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */