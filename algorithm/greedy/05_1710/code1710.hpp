#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        sort(boxTypes.begin(), boxTypes.end(), 
            [](const vector<int>& a, const vector<int>& b) {
                return a[1] > b[1];
            }
        );
        int size = 0, res = 0;
        for (const auto& box : boxTypes) {
            int cur = box[0];
            if (box[0] + size > truckSize) {
                cur = truckSize - size;
                res += box[1] * cur;
                size += cur;
                break;
            }
            res += box[1] * cur;
            size += cur;
        }
        return res;
    }
};