#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<vector<int>> r_range(ranges.size(), vector<int>(2, 0));
        for (int i = 0; i < ranges.size(); ++i) {
            r_range[i][0] = i - ranges[i];
            r_range[i][1] = i + ranges[i];
        }
        sort(r_range.begin(), r_range.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0])
                return a[1] > b[1];
            return a[0] < b[0];
        });
        int res = 0, idx = 0, reach = 0, cur = 0;
        while (cur < n) {
            for (; idx < r_range.size(); ++idx) {
                if (r_range[idx][0] > cur)
                    break;
                if (r_range[idx][0] <= cur && cur <= r_range[idx][1]) {
                    reach = max(reach, r_range[idx][1]);
                }
            }
            if (reach == cur)
                return -1;
            ++res;
            cur = reach;
        }
        return res;
    }
};