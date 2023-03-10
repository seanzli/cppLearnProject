#include <vector>
using namespace std;
class Solution {
    int res;
    void dfs(const vector<int>& nums, int idx, int cur, int m) {
        if (idx == nums.size()) {
            if (cur == m)
                ++res;
            return;
        }
        dfs(nums, idx + 1, cur, m);
        dfs(nums, idx + 1, cur | nums[idx], m);
    }
public:
    int countMaxOrSubsets(vector<int>& nums) {
        res = 0;
        int m = 0;
        for (const auto& itr : nums)
            m |= itr;
        dfs(nums, 0, 0, m);
        return res;
    }
};