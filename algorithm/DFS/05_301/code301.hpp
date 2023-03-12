#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
    unordered_set<string> records;
    vector<string> res;
    int len;
    void dfs(const std::string& s, std::string& cur, int idx, int count, int remove) {
        if (remove > len || count < 0)
            return;
        if (idx == s.size()) {
            if (records.count(cur) == 0 && count == 0 && remove == len) {
                records.insert(cur);
                res.push_back(cur);
            }
            return;
        }
        if (s[idx] == '(') {
            dfs(s, cur, idx + 1, count, remove + 1);
            cur.push_back('(');
            dfs(s, cur, idx + 1, count + 1, remove);
            cur.pop_back();
        }
        else if (s[idx] == ')') {
            dfs(s, cur, idx + 1, count, remove + 1);
            cur.push_back(')');
            dfs(s, cur, idx + 1, count - 1, remove);
            cur.pop_back();
        } else {
            cur += s[idx];
            dfs(s, cur, idx + 1, count, remove);
            cur.pop_back();
        }
        return;
    }
    int lessRemove(const std::string& s) {
        int c = 0;
        int res = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(')
                ++c;
            else if (s[i] == ')') {
                --c;
                if (c < 0) {
                    res++;
                    c = 0;
                }
            }
        }
        return res + c;
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        res.clear();
        len = lessRemove(s);
        string cur = std::string();
        dfs(s, cur, 0, 0, 0);
        return res;
    }
};