#include <vector>

using namespace std;

class Solution {
public:
    int integerReplacement(int n) {
        int res = 0;
        long ln = n;
        while (ln > 1) {
            int a = ln & 0x1;
            if (a == 0) {
                ln = (ln >> 1);
            } else {
                if (ln == 3)
                    return res += 2;
                int b = (ln >> 1) & 0x1;
                if (b == 0)
                    ln = ln - 1;
                else
                    ln = ln + 1;
            }
            ++res;       
        }
        return res;
    }
};