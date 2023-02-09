#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
            [](const vector<int>& a, const vector<int>& b) {
                return a[1] == b[1] ? a[0] > b[0] : a[1] < b[1];
            });
        int a = -1, b = -1, res = 0;
        for (auto& itr : intervals) {
            if (itr[0] > b) {
                b = itr[1];
                a = itr[1] - 1;
                res += 2;
            } else if (itr[0] > a) {
                a = b;
                b = itr[1];
                ++res;
            }
        }
        return res;
    }
};