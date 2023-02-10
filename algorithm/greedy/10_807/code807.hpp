#include <vector>
using namespace std;
class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> herizon(n, 0);
        vector<int> vertical(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                herizon[i] = max(herizon[i], grid[i][j]);
                vertical[j] = max(vertical[j], grid[i][j]); 
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                res += (min(herizon[i], vertical[j]) - grid[i][j]);
            }
        }
        return res;
    }
};