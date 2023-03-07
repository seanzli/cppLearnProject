
class Solution {
    int dfs(int n, int k) {
        if (n == 1)
            return 0;
        int h = dfs(n - 1, k / 2);
        if (k % 2 == 0)
            return h;
        return 1 - h;
    }
public:
    int kthGrammar(int n, int k) {
        k = k - 1; // index start from 0;
        return dfs(n, k);
    }
};