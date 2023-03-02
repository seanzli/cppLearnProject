#include <unordered_set>
#include <vector>
#include <string>
#include <queue>

using namespace std;

static vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

class Solution {
    int row, col, k;
    vector<vector<unordered_set<int>>> marks;
    struct status {
        int x, y;
        int keys;
        status() : x(0), y(0) {}
        status(int _x, int _y, int _keys) : x(_x), y(_y), keys(_keys) {}
    };
    bool isKey(char c) {
        return c >= 'a' && c <= 'f';
    }
    bool valid(vector<string>& grid, status& pos) {
        int i = pos.x, j = pos.y;
        if (i < 0 || i == row || j < 0 || j == col)
            return false;
        if (grid[i][j] == '#')
            return false;
        if (isKey(grid[i][j])) {
            pos.keys |= (1 << (grid[i][j] - 'a'));
            return true;
        }
        if (grid[i][j] == '.' || grid[i][j] == '@') {
            return true;
        }
        int c = grid[i][j] - 'A';
        return (pos.keys & (1 << c)) > 0;
    }
public:
    int shortestPathAllKeys(vector<string>& grid) {
        row = grid.size();
        col = grid[0].length();
        marks = vector<vector<unordered_set<int>>>(row, vector<unordered_set<int>>(col));
        k = 0;
        queue<status> que;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j] >= 'a' && grid[i][j] <= 'f')
                    ++k;
                else if (grid[i][j] == '@')
                    que.push(status(i, j, 0));
            }
        }
        int res = 0;
        while (!que.empty()) {
            int n = que.size();
            for (int i = 0; i < n; ++i) {
                auto cur = que.front(); que.pop();
                if (cur.keys == ((1 << k) - 1))
                    return res;
                for (const auto& itr : dir) {
                    auto cur1 = status(cur.x + itr.first, cur.y + itr.second, cur.keys);
                    if (valid(grid, cur1) && marks[cur1.x][cur1.y].count(cur1.keys) == 0) {
                        que.push(cur1);
                        marks[cur1.x][cur1.y].insert(cur1.keys);
                    }
                }
            }
            ++res;
        }
        return -1;
    }
};