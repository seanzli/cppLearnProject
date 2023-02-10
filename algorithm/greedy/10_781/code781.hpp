#include <map>
#include <vector>
using namespace std;
class Solution {
public:
    int numRabbits(vector<int>& answers) {
        map<int, int> hash; // num, count;
        for (const auto& itr : answers) {
            ++hash[itr + 1];
        }
        int res = 0;
        for (const auto& itr : hash) {
            int n = itr.second / itr.first;
            if (itr.second > n * itr.first)
                ++n;
            res += n * itr.first;
        }
        return res;
    }
};