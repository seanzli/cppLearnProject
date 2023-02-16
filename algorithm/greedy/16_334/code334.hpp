#include <vector>
#include <limits.h>
using namespace std;
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int left = INT_MAX, mid = INT_MAX;
        for (int i = 0; i < nums.size(); ++i) {
            if (left >= nums[i])
                left = nums[i];
            else if (mid >= nums[i])
                mid = nums[i];
            else if (mid < nums[i])
                return true;
        }
        return false;
    }
};