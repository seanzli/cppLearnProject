#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
    struct Node {
        string name;
        unordered_map<string, Node*> next;
        bool isEnd;
        Node(string cur) : name(cur), isEnd(false) {}
    };
    Node* root = nullptr;
    void insert(const string& path) {
        Node* curNode = root;
        string cur = "";
        for (int i = 0; i < path.size(); ++i) {
            if (path[i] == '/') {
                if (cur.empty())
                    continue;
                if (curNode->next.find(cur) == curNode->next.end()) {
                    curNode->next[cur] = new Node(cur);
                }
                curNode = curNode->next[cur];
                if (curNode->isEnd)
                    return;
                cur = "";
            } else {
                cur.push_back(path[i]);
            }
        }
        if (curNode->next.find(cur) == curNode->next.end()) {
            curNode->next[cur] = new Node(cur);
        }
        curNode->next[cur]->isEnd = true;
    }
    void dfs(Node* cur, string& str, vector<string>& res) {
        if (cur == nullptr)
            return;
        if (cur->isEnd) {
            res.push_back(str + "/" + cur->name);
            return;
        }
        string tmp = str + "/" + cur->name;
        for (auto& itr : cur->next) {
            dfs(itr.second, tmp, res);
        }
    }
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        root = new Node(string());
        for (const auto& itr : folder)
            insert(itr);
        vector<string> res;
        string str = "";
        for (auto& itr : root->next) {
            dfs(itr.second, str, res);
        }
        return res;
    }
};