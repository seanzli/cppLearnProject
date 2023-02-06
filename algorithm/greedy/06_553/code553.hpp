#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        if (nums.size() == 1)
            return to_string(nums[0]);
        if (nums.size() == 2)
            return to_string(nums[0]) + "/" + to_string(nums[1]);
        string res = to_string(nums[0]) + "/(";
        for (int i = 1; i < nums.size(); ++i) {
            res += to_string(nums[i]) + "/";
        }
        res.back() = ')';
        return res;
    }
};