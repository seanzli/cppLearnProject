#include <vector>
using namespace std;
class Solution {
    int row, col;
    vector<vector<bool>> visited;
    int res;
    void dfs(const vector<vector<int>>& grid, int i, int j, int count) {
        if (i < 0 || i == row || j < 0 || j == col) {
            res = max(res, count);
            return;
        }
        if (visited[i][j]) {
            res = max(res, count);
            return;
        }
        if (grid[i][j] == 0) {
            res = max(res, count);
            return;
        }
        count += grid[i][j];
        visited[i][j] = true;
        dfs(grid, i + 1, j, count);
        dfs(grid, i - 1, j, count);
        dfs(grid, i, j + 1, count);
        dfs(grid, i, j - 1, count);
        visited[i][j] = false;
    }
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        res = 0;
        row = grid.size();
        col = grid[0].size();
        visited = vector<vector<bool>>(row, vector<bool>(col, false));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                int current = 0;
                dfs(grid, i, j, current);
            }
        }
        return res;
    }
};