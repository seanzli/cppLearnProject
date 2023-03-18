#include <string>

using namespace std;
class Solution {
    bool isPalindrome(const string& str, int left, int right) {
        while (left < right) {
            if (str[left++] != str[right--])
                return false;
        }
        return true;
    }
    bool helper(const string& a, const string& b) {
        int left = 0, right = b.size() - 1;
        while (left < a.size() && right >= 0) {
            if (isPalindrome(b, left, right))
                return true;
            if (isPalindrome(a, left, right))
                return true;
            if (a[left] == b[right]) {
                left++;
                right--;
            } else {
                return false;
            }
        }
        return false;
    }
public:
    bool checkPalindromeFormation(string a, string b) {
        return helper(a, b) || helper(b, a);
    }
};