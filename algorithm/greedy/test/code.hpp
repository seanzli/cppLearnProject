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
        int dif = 0;
        if (sum1 > sum2) {
            swap(nums1, nums2); // nums1 < nums2
            dif = sum1 - sum2;
        } else 
            dif = sum2 - sum1;
        
        vector<int> count(6, 0);
        for (auto& itr : nums1)
            ++count[6 - itr];
        for (auto& itr : nums2)
            ++count[itr - 1];
        
        int res = 0;
        for (int i = 5; i >= 0 && dif > 0; --i) {
            if (i * count[i] > dif)
                return res + (dif + i - 1) / i;
            res += count[i];
            dif -= i * count[i];
        }
        return -1;
    }
};