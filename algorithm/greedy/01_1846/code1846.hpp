#include <algorithm>

class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(std::vector<int>& arr) {
        std::sort(arr.begin(), arr.end());
        int res = 1;
        for (int idx = 0; idx < arr.size(); ++idx) {
            if (arr[idx] < res)
                res = arr[idx];
            ++res;
        }
        return res - 1;
    }
};