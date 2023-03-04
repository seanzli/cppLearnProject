#include <vector>
#include <queue>
using namespace std;
class Solution {
    int row, col;
    vector<vector<char>> mark;
    struct Pos {
        int x, y;
        Pos() : x(0), y(0) {}
        Pos(int _x, int _y) : x(_x), y(_y) {}
        Pos operator+(const Pos& lhs) {
            return Pos(x + lhs.x, y + lhs.y);
        }
        bool isValid(int row, int col) {
            return x >= 0 && x < row && y >= 0 && y < col;
        }
    };
    const vector<Pos> dis{Pos(1, 0), Pos(-1, 0), Pos(0, 1), Pos(0, -1)};
    void check(const Pos& start, const char flag, const vector<vector<int>>& heights) {
        queue<Pos> que;
        que.push(start);
        vector<vector<bool>> checked(row, vector<bool>(col, false));
        checked[start.x][start.y] = true;
        while (!que.empty()) {
            int n = que.size();
            for (int j = 0; j < n; ++j) {
                auto cur = que.front(); que.pop();
                mark[cur.x][cur.y] |= flag;
                for (const auto& itr : dis) {
                    auto next = cur + itr;
                    if (next.isValid(row, col) && 
                        ((mark[next.x][next.y] & flag) == 0) && // not check yet
                        checked[next.x][next.y] == false &&
                        heights[next.x][next.y] >= heights[cur.x][cur.y]) {
                        que.push(next);
                        checked[next.x][next.y] = true;
                    }
                }
            }
        }
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        row = heights.size();
        col = heights[0].size();
        mark = vector<vector<char>>(row, vector<char>(col, 0)); // p = 0x01, a = 0x10 
        for (int i = 0; i < row; ++i) {
            check(Pos(i, 0), 0x01, heights);
            check(Pos(i, col - 1), 0x10, heights);
        }
        for (int i = 0; i < col; ++i) {
            check(Pos(0, i), 0x01, heights);
            check(Pos(row - 1, i), 0x10, heights);
        }
        vector<vector<int>> res;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (mark[i][j] == 0x11) {
                    res.push_back(vector<int>{i, j});
                }
            }
        }
        return res;
    }
};