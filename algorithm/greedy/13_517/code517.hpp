#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int sum = accumulate(machines.begin(), machines.end(), 0);
        int average = sum / machines.size();
        if (average * machines.size() < sum)
            return -1;
        int res = 0;
        sum = 0;
        for_each(machines.begin(), machines.end(), [&](const int itr) {
            int dif = itr - average;
            sum += dif;
            res = max(res, max(abs(sum), dif));
        });
        return res;
    }
};