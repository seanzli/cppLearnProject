#include <vector>
#include <algorithm>
using namespace std;
class Solution {
    int costTime(const vector<int>& piles, int speed) {
        int cost = 0;
        for (const auto& itr : piles) {
            cost += (itr + speed - 1) / speed;
        }
        return cost;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1, right = *max_element(piles.begin(), piles.end());
        while (left < right) {
            int mid = left + (right - left) / 2;
            int cost = costTime(piles, mid);
            if (cost <= h) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};