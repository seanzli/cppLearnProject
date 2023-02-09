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
        
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end(), [](const int& a, const int& b) {return a > b;});
        int idx1 = 0, idx2 = 0, res = 0;
        while (idx1 < nums1.size() && idx2 < nums2.size() && dif > 0) {
            int dif1 = 6 - nums1[idx1];
            int dif2 = nums2[idx2] - 1;
            if (dif1 > dif2) {
                ++idx1;
                dif -= dif1;
            } else {
                ++idx2;
                dif -= dif2;
            }
            ++res;
        }
        while (idx1 < nums1.size() && dif > 0) {
            dif -= (6 - nums1[idx1++]);
            ++res;
        }
        while (idx2 < nums2.size() && dif > 0) {
            dif -= (nums2[idx2++] - 1);
            ++res;
        }
        return dif > 0 ? -1 : res;
    }
};