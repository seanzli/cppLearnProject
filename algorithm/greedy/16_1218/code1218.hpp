#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        unordered_map<int, int> hash; // value, count;
        int max_len = 1;
        for (const auto& itr : arr) {
            if (hash.count(itr - difference) == 0)
                hash[itr] = 1;
            else {
                hash[itr] = hash[itr - difference] + 1;
                max_len = max(max_len, hash[itr]);
            }
        }
        return max_len;
    }
};