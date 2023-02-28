#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](const int a, const int b) {
            return to_string(a) + to_string(b) > to_string(b) + to_string(a);
        });
        string res = "";
        for (const int itr : nums)
            res = res + to_string(itr);
        if (res[0] == '0')
            return "0";
        return res;
    }
};