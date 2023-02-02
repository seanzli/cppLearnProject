#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int max_value = 0;
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            max_value = max(max_value, nums[left++] + nums[right--]);
        }
        return max_value;
    }
};