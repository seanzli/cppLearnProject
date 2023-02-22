#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

class Solution {
    struct Tire {
        Tire* next[2];
        Tire() {
            next[0] = nullptr;
            next[1] = nullptr;
        }
        ~Tire() {
            if (next[0]) {
                delete next[0];
                next[0] = nullptr;
            }
            if (next[1]) {
                delete next[1];
                next[1] = nullptr;
            }
        }
    };
    Tire* root = nullptr;
    void add(int x) {
        Tire* cur = root;
        for (int i = 31; i >= 0; --i) {
            int t = (x >> i) & 0x1;
            if (cur->next[t] == nullptr)
                cur->next[t] = new Tire();
            cur = cur->next[t];
        }
    }
    int get(int x) {
        Tire* cur = root;
        int res = 0;
        for (int i = 31; i >= 0; --i) {
            int a = (x >> i) & 0x1, b = 1 - a;
            if (cur->next[b] != nullptr) {
                res |= (b << i);
                cur = cur->next[b];
            } else {
                res |= (a << i);
                cur = cur->next[a];
            }
        }
        return res;
    }
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        root = new Tire();
        sort(nums.begin(), nums.end());
        vector<pair<vector<int>, int>> vec(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            vec[i] = make_pair(queries[i], i); // vec[value, max], idx;
        }
        sort(vec.begin(), vec.end(),
            [](const pair<vector<int>, int>& a, const pair<vector<int>, int>& b) {
                return a.first[1] < b.first[1];
            }
        );
        vector<int> res(queries.size(), INT_MIN);
        int idx = 0; // nums
        for (int i = 0; i < vec.size(); ++i) {
            for ( ; idx < nums.size(); ++idx) {
                if (vec[i].first[1] >= nums[idx])
                    add(nums[idx]);
                else
                    break;
            }
            if (idx == 0)
                res[vec[i].second] = -1;
            else {
                int b = get(vec[i].first[0]);
                res[vec[i].second] = b ^ vec[i].first[0];
            }
        }
        delete root;
        return res;
    }
};