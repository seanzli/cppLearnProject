#include <algorithm>

using namespace std;

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int left = 0, right = people.size() - 1;
        int res = 0;
        while (left <= right) {
            if (limit >= people[left] + people[right]) {
                ++left;
                --right;
            } else {
                --right;
            }
            ++res;
        }
        return res;
    }
};