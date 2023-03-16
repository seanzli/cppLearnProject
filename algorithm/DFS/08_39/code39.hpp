#include <vector>
#include <algorithm>
using namespace std;
class Solution {
    vector<vector<int>> res;
    void dfs(const vector<int>& candidates, int idx, vector<int>& cur, int target) {
        if (target == 0) {
            res.push_back(cur);
            return;
        }
        for (int i = idx; i < candidates.size(); ++i) {
            if (target < candidates[i])
                return;
            cur.push_back(candidates[i]);
            dfs(candidates, i, cur, target - candidates[i]);
            cur.pop_back();
        }
        return;
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        res.clear();
        vector<int> cur;
        sort(candidates.begin(), candidates.end());
        dfs(candidates, 0, cur, target);
        return res;
    }
};