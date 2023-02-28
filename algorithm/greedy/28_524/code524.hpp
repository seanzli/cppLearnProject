#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
    bool check(const string& s, const string& itr) {
        int idx = 0, count = 0;
        for (int i = 0 ; i < itr.size(); ++i) {
            for ( ; idx < s.size(); ++idx) {
                if (s[idx] == itr[i]) {
                    ++idx;
                    ++count;
                    break;
                }
            }
        }
        return count == itr.size();
    }
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        sort(dictionary.begin(), dictionary.end(), [](const string& a, const string& b) {
            return a.size() == b.size() ? a < b : a.size() > b.size();
        });
        for (const auto& itr : dictionary) {
            if (check(s, itr))
                return itr;
        }
        return string();
    }
};