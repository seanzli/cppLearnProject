#include <vector>
#include <string>
#include <algorithm>

using namespace std;
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        vector<pair<int, char>> vec = {{a, 'a'}, {b, 'b'}, {c, 'c'}};
        string res = "";
        while (1) {
            sort(vec.begin(), vec.end());
            if (vec[2].first == 0)
                return res;
            if (res.size() < 2) {
                res.push_back(vec[2].second);
                --vec[2].first;
            } else if (res[res.size() - 1] != res[res.size() - 2]) {
                res.push_back(vec[2].second);
                --vec[2].first;
            } else if (res.back() != vec[2].second) {
                res.push_back(vec[2].second);
                --vec[2].first;
            } else if (vec[1].first > 0) {
                res.push_back(vec[1].second);
                --vec[1].first;
            } else {
                return res;
            }
        }
        return res;
    }
};