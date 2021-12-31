#include <vector>
#include <functional>

template<typename T, typename Cmp>
void sort(std::vector<T>& in,
          const size_t c_left,
          const size_t c_right,
          Cmp& cmp) {
    if (c_left >= c_right)
        return;
    size_t left = c_left, right = c_right;
    size_t idx = left;
    size_t i = left + 1;
    while (i <= right) {
        if (cmp(in[i], in[idx])) {
            std::swap(in[i], in[left++]);
            idx = left;
            i = left + 1;
        } else {
            std::swap(in[i], in[right--]);
        }
    }
    sort(in, c_left, idx - 1, cmp);
    sort(in, idx + 1, c_right, cmp);
}

template<typename T, typename Cmp = std::function<bool(T, T)>>
void sort(std::vector<T>& in, Cmp cmp = std::less<T>()) {
    sort(in, 0, in.size() - 1, cmp);
}