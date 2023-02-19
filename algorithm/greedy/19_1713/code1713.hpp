#include <vector>
#include <unordered_map>>
using namespace std;
class Solution {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        unordered_map<int, int> hash; // value -> idx;
        for (int i = 0; i < target.size(); ++i) {
            hash[target[i]] = i;
        }

        vector<int> idx;
        for (const auto& val : arr) {
            if (hash.find(val) != hash.end()) {
                int cur = hash[val];
                auto itr = lower_bound(idx.begin(), idx.end(), cur);
                if (itr == idx.end())
                    idx.push_back(cur);
                else
                    *itr = cur;
            }
        }
        return target.size() - idx.size();
    }
};