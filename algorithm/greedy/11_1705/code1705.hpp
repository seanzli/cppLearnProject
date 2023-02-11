#include <vector>
#include <queue>
using namespace std;
class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int res = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // day, count
        int day = 0;
        while (day < days.size()) {
            while (!pq.empty() && pq.top().first <= day) {
                pq.pop();
            }
            if (apples[day] > 0) {
                pq.emplace(day + days[day], apples[day]);
            }
            if (!pq.empty()) {
                auto cur = pq.top(); pq.pop();
                if ((--cur.second) != 0) {
                    pq.emplace(cur.first, cur.second);
                }
                res++;
            }
            ++day;
        }
        while (!pq.empty()) {
            while (!pq.empty() && pq.top().first <= day) {
                pq.pop();
            }
            if (pq.empty()) {
                break;
            }
            auto cur = pq.top(); pq.pop();
            int num = min(cur.first - day, cur.second);
            res += num;
            day += num;
        }
        return res;
    }
};