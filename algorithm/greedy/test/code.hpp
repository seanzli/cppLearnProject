#include <vector>
#include <algorithm>
#include <numeric>
#include <limits.h>

using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        vector<int>m(n,INT_MAX);
        for(int i = n-2; i>=0; i--){
            m[i] = min(m[i+1], arr[i+1]);
        }
        int currMax = 0;
        int res =0 ;
        for(int i = 0;i<n;i++){
            currMax = max(currMax, arr[i]);
            if(currMax <= m[i]){
                res++;
            }
        }
        return res;
    }
};