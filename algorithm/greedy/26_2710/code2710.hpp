#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        unordered_map<int, int> even; // value, count idx = 0, 2, 4
        unordered_map<int, int> odd;  // value, count idx = 1, 3, 5 
        for (int i = 0; i < nums.size(); ++i) {
            if ((i & 0x1) == 0)
                ++even[nums[i]];
            else
                ++odd[nums[i]];
        }
        vector<pair<int, int>> even_vec, odd_vec;
        for (const auto& itr : even) {
            even_vec.push_back(make_pair(itr.second, itr.first)); // count , value
        }
        for (const auto& itr : odd) {
            odd_vec.push_back(make_pair(itr.second, itr.first)); // count, value
        }
        even_vec.push_back(make_pair(0, 0));
        odd_vec.push_back(make_pair(0, 0));
        sort(even_vec.begin(), even_vec.end(), ::greater<>());
        sort(odd_vec.begin(), odd_vec.end(), ::greater<>());
        if (even_vec[0].second != odd_vec[0].second) {
            // max count value are the same at odd and even
            return nums.size() - even_vec[0].first - odd_vec[0].first;
        }
        return nums.size() - max(even_vec[0].first + odd_vec[1].first, 
                       even_vec[1].first + odd_vec[0].first);
    }
};