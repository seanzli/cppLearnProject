#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        vector<int> idx1(nums1.size(), 0);
        vector<int> idx2(nums2.size(), 0);
        iota(idx1.begin(), idx1.end(), 0);
        iota(idx2.begin(), idx2.end(), 0);
        // increase sequence -> idx
        sort(idx1.begin(), idx1.end(), [&] (int a, int b) {return nums1[a] < nums1[b];});
        sort(idx2.begin(), idx2.end(), [&] (int a, int b) {return nums2[a] < nums2[b];});

        vector<int> res(nums1.size(), 0);
        int left = 0, right = nums1.size() - 1;
        for (int i = 0; i < res.size(); ++i) {
            if (nums1[idx1[i]] > nums2[idx2[left]]) { // large than nums2, write nums2
                res[idx2[left]] = nums1[idx1[i]];
                ++left;
            } else {
                res[idx2[right]] = nums1[idx1[i]];  // else use the largest nums2
                --right;
            }
        }
        return std::move(res);
    }
};