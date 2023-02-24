#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int count = 0;
        unordered_map<int, int> hash; // value -> idx
        for (int i = 0; i < row.size(); ++i) {
            hash[row[i]] = i;
        }
        for (int i = 0; i < row.size(); i+=2){
            int cur = row[i] ^ 1; // partner
            if (hash[cur] == i + 1)
                continue;
            int partner_idx = hash[cur];
            swap(row[partner_idx], row[i + 1]); // swap;
            hash[row[partner_idx]] = partner_idx;
            ++count;
        }
        return count;
    }
};