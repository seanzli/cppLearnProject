#include <queue>
#include <vector>
using namespace std;
class Solution {
    struct Pos {
        int x;
        int y;
        int s;
        Pos(int _x, int _y, int _s) : x(_x), y(_y), s(_s) {}
        Pos right() {
            return Pos(x, y + 1, s);
        }
        Pos down() {
            return Pos(x + 1, y, s);
        }
        Pos rotate() {
            return Pos(x, y, s^3);
        }
    };
    // 1(01) = horizontal, 2(10) = vertical
    vector<vector<int>> m_state;
    int m_size;
    bool stateCheck(const vector<vector<int>>& grid, const Pos& pos) {
        if (pos.x == m_size || pos.y == m_size)
            return false;
        if ((m_state[pos.x][pos.y] & pos.s) > 0 || grid[pos.x][pos.y] == 1)
            return false;
        if (pos.s == 1) {
            if (pos.y + 1 == m_size || grid[pos.x][pos.y + 1] == 1)
                return false;
        } else {
            if (pos.x + 1 == m_size || grid[pos.x + 1][pos.y] == 1)
                return false;
        }
        return true;
    }
    bool canRot(const vector<vector<int>>& grid, const Pos& pos) {
        if (pos.x + 1 == m_size || pos.y + 1 == m_size)
            return false;
        if (grid[pos.x + 1][pos.y + 1] == 1)
            return false;
        return true;
    }
    void mark(const Pos& pos) {
        m_state[pos.x][pos.y] |= pos.s; 
    }
public:
    int minimumMoves(vector<vector<int>>& grid) {
        m_size = grid.size();
        m_state = vector<vector<int>>(m_size, vector<int>(m_size, 0));
        m_state[0][0] = 0x01;
        queue<Pos> que;
        que.push(Pos(0, 0, 0x01));
        int res = 0;
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; ++i) {
                auto cur = que.front(); que.pop();
                if (cur.x == m_size - 1 && cur.y == m_size - 2 && cur.s == 0x01)
                    return res;
                auto right = cur.right();
                if (stateCheck(grid, right)) {
                    que.push(right);
                    mark(right);
                }
                auto down = cur.down();
                if (stateCheck(grid, down)) {
                    que.push(down);
                    mark(down);
                }
                if (canRot(grid, cur)) {
                    auto rot = cur.rotate();
                    if (stateCheck(grid, rot)) {
                        que.push(rot);
                        mark(rot);
                    }
                }
                
            }
            ++res;
        }
        return -1;
    }
};