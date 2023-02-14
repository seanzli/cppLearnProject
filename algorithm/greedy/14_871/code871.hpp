#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int, vector<int>, ::less<>> que;
        int res = 0;
        int reach = startFuel;
        int idx = 0;
        do {
            if (reach >= target)
                return res;
            for ( ; idx < stations.size() && stations[idx][0] <= reach; ++idx) {
                que.push(stations[idx][1]);
            }
            if (que.empty())
                return -1;
            reach += que.top(); que.pop();
            ++res;
        } while (1);
        return -1;
    }
};