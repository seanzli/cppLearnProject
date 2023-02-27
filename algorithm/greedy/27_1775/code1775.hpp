#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int sum1 = accumulate(nums1.begin(), nums1.end(), 0);
        int sum2 = accumulate(nums2.begin(), nums2.end(), 0);
        if (sum1 == sum2)
            return 0;
        if (sum1 < sum2) // nums1 > nums2;
            swap(nums1, nums2);
        int dif = abs(sum1 - sum2);
        vector<int> count(6, 0); // 1-5, modify count;
        for (const auto& itr : nums1)
            ++count[itr - 1]; // decrease nums1
        for (const auto& itr : nums2)
            ++count[6 - itr]; // increase nums2
        int res = 0;
        for (int i = 5; i > 0; --i) {
            if (dif <= count[i] * i)
                return res + (dif + i - 1) / i;
            dif -= count[i] * i;
            res += count[i];
        }
        return -1;
    }
};