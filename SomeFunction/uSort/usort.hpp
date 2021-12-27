#include <vector>
#include <functional>



template<typename T>
void cut(const std::vector<T>& in, std::vector<T>& left, std::vector<T>& right) {
    size_t size = in.size();
    left = std::vector<T>(in.begin(), in.begin() + size / 2);
    right = std::vector<T>(in.begin() + size / 2, in.end());
}

template<typename T, typename Cmp>
void merge(const std::vector<T>& left,
           const std::vector<T>& right,
           std::vector<T>& out,
           Cmp& fun) {
    size_t idx_left = 0, idx_right = 0;
    out.clear();
    while (idx_left < left.size() && idx_right < right.size()) {
        out.push_back(fun(left[idx_left], right[idx_right])
                ? left[idx_left++]
                : right[idx_right++]);
    }
    while (idx_left < left.size())
        out.push_back(left[idx_left++]);
    while (idx_right < right.size())
        out.push_back(right[idx_right++]);
}

template<typename T, typename Comp>
void sort(std::vector<T>& in, Comp& fun) {
    if (in.size() < 2)
        return;
    std::vector<T> left, right;
    cut(in, left, right);
    sort(left, fun);
    sort(right, fun);
    merge(left, right, in, fun);
    return;
}