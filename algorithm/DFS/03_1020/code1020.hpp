#include <vector>
using namespace std;
class Solution {
    int row, col;
    bool dfs(vector<vector<int>>& grid, int i, int j, int flag, int& count) {
        if (i < 0 || i == row || j < 0 || j == col)
            return true;
        if (grid[i][j] == 0)
            return true;
        if (i == 0 || i == row - 1 || j == 0 || j == col - 1)
            return false;
        if (grid[i][j] == flag)
            return true;
        ++count;
        grid[i][j] = flag;
        if (dfs(grid, i + 1, j, flag, count) == false)
            return false;
        if (dfs(grid, i - 1, j, flag, count) == false)
            return false;
        if (dfs(grid, i, j + 1, flag, count) == false)
            return false;
        if (dfs(grid, i, j - 1, flag, count) == false)
            return false;
        return true;
    }
public:
    int numEnclaves(vector<vector<int>>& grid) {
        row = grid.size();
        col = grid[0].size();
        int res = 0;
        int flag = 2;
        for (int i = 1; i < row - 1; ++i) {
            for (int j = 1; j < col - 1; ++j) {
                if (grid[i][j] == 1) {
                    int count = 0;
                    if (dfs(grid, i, j, flag, count))
                        res += count;
                    ++flag;
                }
            }
        }
        return res;
    }
};