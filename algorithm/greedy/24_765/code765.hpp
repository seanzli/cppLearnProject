#include <vector>

using namespace std;

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int count = 0;
        for (int i = 0; i < row.size(); i+=2){
            int cur = row[i] ^ 1;
            if (row[i+1] == cur)
                continue;
            for (int j = i + 2; j < row.size(); j++){
                if (row[j] == cur){
                    swap(row[i+1], row[j]);
                    count++;
                    break;
                }
            }
        }
        return count;
    }
};