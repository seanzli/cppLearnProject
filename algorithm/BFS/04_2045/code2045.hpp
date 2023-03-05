#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>

using namespace std;

class Solution {
    int nextTime(int cur, int next, int change) {
        int t = cur % (2 * change);
        if (t < change) // 
            return cur + next;
        return cur + (2 * change) - t + next;
    }
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        unordered_map<int, unordered_set<int>> hash;
        vector<vector<int>> c(n + 1, vector<int>(2,INT_MAX)); // only reach twice
        for (const auto& itr : edges) {
            hash[itr[0]].insert(itr[1]);
            hash[itr[1]].insert(itr[0]);
        }
        queue<pair<int, int>> que; // {node ,step}
        que.push({1, 0});
        while (!que.empty() && c[n][1] == INT_MAX) {
            int size = que.size();
            for (int i = 0; i < size; ++i) {
                auto cur = que.front(); que.pop();
                for (const auto& itr : hash[cur.first]) {
                    int step = cur.second + 1;
                    if (step < c[itr][0]) {
                        c[itr][1] = c[itr][0];
                        c[itr][0] = step;
                        que.push({itr, step});
                    } else if (step > c[itr][0] && step < c[itr][1]) {
                        c[itr][1] = step;
                        que.push({itr, step});
                    }
                }
            }
        }
        int res = 0;
        for (int i = 0; i < c[n][1]; ++i) {
            res = nextTime(res, time, change);
        }
        return res;
    }
};