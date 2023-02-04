#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        vector<pair<int, int>> sorted(arr.size());
        for (auto i = 0; i < arr.size(); ++i) {
            sorted[i] = make_pair(arr[i], i);
        }
        sort(sorted.begin(), sorted.end());
        string arr_str(arr.size(), '0');
        string cmp_str(arr.size(), '0');
        int res = 0;
        for (auto i = 0; i < arr.size(); ++i) {
            arr_str[i] = '1';
            cmp_str[sorted[i].second] = '1';
            if (arr_str == cmp_str)
                ++res;
        }
        return res;
    }
};