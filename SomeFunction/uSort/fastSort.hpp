#include <vector>

void sort(std::vector<int>& in,
          const size_t c_left,
          const size_t c_right) {
    if (c_left >= c_right)
        return;
    size_t left = c_left, right = c_right;
    size_t idx = left;
    size_t i = left + 1;
    while (i <= right) {
        if (in[i] > in[idx]) {
            std::swap(in[i], in[right--]);
        } else {
            std::swap(in[i], in[left++]);
            idx = left;
            i = left + 1;
        }
    }
    sort(in, c_left, idx - 1);
    sort(in, idx + 1, c_right);
}

void sort(std::vector<int>& in) {
    sort(in, 0, in.size() - 1);
}