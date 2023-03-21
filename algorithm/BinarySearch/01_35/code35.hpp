#include <vector>
using namespace std;
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        int mid = left + (right - left) / 2;
        while (right - left > 1) {
            if (nums[mid] == target)
                return mid;
            if (nums[mid] < target)
                left = mid;
            if (nums[mid] > target)
                right = mid;
            mid = left + (right - left) / 2;
        }
        if (nums[right]<target)
            return right+1;
        if (nums[mid]<target)
            return right;
        if (nums[left]<target)
            return mid;
        return left;
    }
};