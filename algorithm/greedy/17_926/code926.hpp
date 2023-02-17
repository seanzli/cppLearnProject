#include <string>

using namespace std;

class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int count0 = 0;
        for (const auto& itr : s) {
            if (itr == '0')
                ++count0; // all '0'
        }
        int count1 = 0;
        int res = count0; // pointer before 0, all '0' need to flip to '1'
        for (const auto& itr : s) {
            if (itr == '0') {
                --count0; // '0' after this pointer
            } else {
                ++count1; // '1' before this pointer
            }
            res = min(res, count0 + count1);
        }
        return res;
    }
};