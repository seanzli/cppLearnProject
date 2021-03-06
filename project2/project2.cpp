#include "project2.h"

#include <fstream>
#include <vector>
#include <algorithm>

int char2num(const char c) {
    if ('0' <= c && c <= '9')
        return c - '0';
    else if ('a' <= c && c <= 'z')
        return c - 'a' + 10;
    return 0;
}

char num2char(int n) {
    if (0 <= n && n <= 9)
        return '0' + n;
    else if (10 <= n && n <= 36)
        return 'a' + n - 10;
    return ' ';
}

/// @brief  add string, all input string and output string range by low->high;
/// @param  add1 should have checked validable
///         add2 
std::string add(const std::string& add1, const std::string& add2, const unsigned int base) {
    std::string res = "";
    int idx1 = 0, idx2 = 0;
    int flag = 0; /// last add large than base
    while (idx1 < add1.size() || idx2 < add2.size()) {
        /// add
        int cur = flag;
        if (idx1 < add1.size())
            cur += char2num(add1[idx1++]);
        if (idx2 < add2.size())
            cur += char2num(add2[idx2++]);

        /// carry check
        if (cur >= base) {
            flag = 1;
            cur -= base;
        } else {
            flag = 0;
        }

        /// add to output
        res.push_back(num2char(cur));
    }
    
    /// check last carry
    if (flag)
        res.push_back(num2char(flag));

    while (res.size() && res.back() == '0') {
        res.pop_back();
    }
    
    return res.size() == 0 ? "0" : res;
}

///@brief sub string  sub1 is large than sub2
std::string sub(const std::string& sub1, const std::string& sub2, const unsigned int base) {
    std::string res = "";
    int flag = 0; //borrow  0 or -1;
    int idx1 = 0, idx2 = 0;
    while (idx1 < sub1.size() || idx2 < sub2.size()) {
        int cur = flag;
        if (idx1 < sub1.size())
            cur += char2num(sub1[idx1++]);
        if (idx2 < sub2.size())
            cur -= char2num(sub2[idx2++]);
        if (cur < 0) {
            cur += base;
            flag = -1;
        } else {
            flag = 0;
        }
        res.push_back(num2char(cur));
    }
    while (res.size() && res.back() == '0') {
        res.pop_back();
    }
    
    return res.size() == 0 ? "0" : res;
}

/// @brief  compare string
/// @param  return   0: str1 == str2
///                  1: str1 >  str2
///                 -1: str1 <  str2
int stringCompare(const std::string& str1, const std::string& str2) {
    if (str1 == str2)
        return 0;
    if (str1.size() > str2.size())
        return 1;
    else if (str1.size() < str2.size())
        return -1;
    for (int i = str1.size() - 1; i >= 0; --i) {
        if (str1[i] == str2[i])
            continue;
        int c1 = char2num(str1[i]);
        int c2 = char2num(str2[i]);
        if (c1 > c2)
            return 1;
        return -1;
    }
    return 0;
}

/// @brief  check input string is valid or not, low -> high, sign should be at last
bool stringValid(const std::string& str, const unsigned int base, const bool bSigned) {
    if ((str.back() == '+' || str.back() == '-') && bSigned == false)
        return stringValid(str.substr(0, str.size() - 1), base, true);
    for (const char& c : str) {
        if (c == '+' || c == '-')
            return false;
        if (char2num(c) >= base)
            return false;
    }
    return true;
}

/// @brief  add str1 and str2
std::string sum(const std::string& str1, const std::string& str2, const unsigned int base) {
    /// delete '+'
    if (str1.back() == '+')
        return sum(str1.substr(0, str1.size() - 1), str2, base);
    if (str2.back() == '+')
        return sum(str1, str2.substr(0, str2.size() - 1), base);
    
    /// all negative
    if (str1.back() == '-' && str2.back() == '-') {
        std::string res = add(str1.substr(0, str1.size() - 1), str2.substr(0, str2.size() - 1), base);
        return res + "-";
    }

    /// str1 negative
    if (str1.back() == '-') {
        std::string str = str1.substr(0, str1.size() - 1);
        int i_compare = stringCompare(str, str2);
        if (i_compare == 0)
            return "0";
        else if (i_compare > 0) {
            std::string res = sub(str, str2, base);
            return res + "-";
        } else {
            return sub(str2, str1, base);
        }
    }

    /// str2 negative
    if (str2.back() == '-') {
        return sum(str2, str1, base);
    }

    /// all positive
    return add(str1, str2, base);
}

unsigned decode_file(const std::string file_path, std::string& add1, std::string& add2) {
    std::ifstream fin(file_path);

    std::string cur;
    std::vector<std::string> vec;
    if (fin) {
        while (std::getline(fin, cur)) {
            vec.emplace_back(cur);
        }
    } else {
        return 1;
    }

    if (vec.size() != 2) {
        return 2;
    }
    add1 = vec[0];
    add2 = vec[1];

    for (char &c : add1) {
        if ('A' <= c && c <= 'Z')
            c = c - 'A' + 'a';
    }
    for (char &c : add2) {
        if ('A' <= c && c <= 'Z')
            c = c - 'A' + 'a';
    }

    return 0;
}

void changeBase(std::string& str, const int in_base, const int out_base) {
    std::vector<int> input;
    bool positive = true;
    int i = 0;
    if (str[0] == '-') {
        i = 1;
        positive = false;
    }
    
    for ( ; i < str.size(); ++i)
        input.push_back(char2num(str[i]));

    std::reverse(input.begin(), input.end());

    std::vector<int> res;
    while(input.size())
    {
        int r = 0;
        for(int i = input.size() - 1; i >= 0; i--)
        {
            input[i] += r * in_base;
            r = input[i] % out_base;
            input[i] /= out_base;
        }
        res.push_back(r);
        while(input.size() && input.back() == 0)
            input.pop_back();
    }

    std::reverse(res.begin(), res.end());

    if (positive)
        str = "";
    else
        str = "-";
    for (int& itr : res)
        str += num2char(itr);
    return;
}