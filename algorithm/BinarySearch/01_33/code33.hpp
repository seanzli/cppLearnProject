#include <vector>
using namespace std;
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[left] <= nums[mid]) {// left -> mid, sorted
                if (target < nums[left] || target > nums[mid])
                    left = mid + 1;
                else
                    right = mid;
            } else { // mid -> left, sort
                if (target < nums[mid] || target > nums[right])
                    right = mid - 1;
                else
                    left = mid;
            }
        }
        return -1;
    }
};