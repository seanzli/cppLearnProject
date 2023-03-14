#include <vector>
#include <string>
using namespace std;
class Solution {
    int res;
    bool addMark(vector<int>& mark, const string& str) {
        bool checked = true;
        for (const auto& c : str) {
            ++mark[c - 'a'];
            if (mark[c - 'a'] > 1)
                checked = false;
        }
        return checked;
    }
    void subMark(vector<int>& mark, const string& str) {
        for (const auto& c : str)
            --mark[c - 'a'];
    }
    void dfs(const vector<string>& arr, int idx, vector<int>& mark, int count) {
        if (idx == arr.size()) {
            res = max(res, count);
            return;
        }
        if (res == 26)
            return;
        dfs(arr, idx + 1, mark, count);
        bool valid = addMark(mark, arr[idx]);
        if (valid) {
            count += arr[idx].size();
            dfs(arr, idx + 1, mark, count);
        }
        subMark(mark, arr[idx]);
        return;
    }
public:
    int maxLength(vector<string>& arr) {
        vector<int> mark(26, 0);
        res = 0;
        int count = 0;
        dfs(arr, 0, mark, count);
        return res;
    }
};