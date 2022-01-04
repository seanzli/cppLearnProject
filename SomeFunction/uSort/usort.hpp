#include <vector>
#include <functional>
//
//template<typename T>
//void cut(const std::vector<T>& in, std::vector<T>& left, std::vector<T>& right) {
//    size_t size = in.size();
//    left = std::vector<T>(in.begin(), in.begin() + size / 2);
//    right = std::vector<T>(in.begin() + size / 2, in.end());
//}
//
//template<typename T, typename Cmp>
//void merge(const std::vector<T>& left,
//           const std::vector<T>& right,
//           std::vector<T>& out,
//           Cmp& fun) {
//    size_t idx_left = 0, idx_right = 0;
//    out.clear();
//    while (idx_left < left.size() && idx_right < right.size()) {
//        out.push_back(fun(left[idx_left], right[idx_right])
//                ? left[idx_left++]
//                : right[idx_right++]);
//    }
//    while (idx_left < left.size())
//        out.push_back(left[idx_left++]);
//    while (idx_right < right.size())
//        out.push_back(right[idx_right++]);
//}
//
//template<typename T, typename Comp>
//void sort(std::vector<T>& in, Comp& fun) {
//    if (in.size() < 2)
//        return;
//    std::vector<T> left, right;
//    cut(in, left, right);
//    sort(left, fun);
//    sort(right, fun);
//    merge(left, right, in, fun);
//    return;
//}

/**
 * merge function
 * @tparam T        vector value_type
 * @tparam Cmp      compare function type
 * @param in        input vector<T>
 * @param left      left part start index
 * @param mid       left part end index, right part should start at mid + 1
 * @param right     right part end index
 * @param fun       compare function, should return bool
 */
template<typename T, typename Cmp>
void merge(std::vector<T>& in, size_t left, size_t mid, size_t right, Cmp& fun) {
    std::vector<T> cur;
    cur.reserve(right - left + 1);
    size_t idx1 = left, idx2 = mid + 1;
    while (idx1 <= mid && idx2 <= right) {
        cur.push_back(
                fun(in[idx1], in[idx2]) ? in[idx1++] : in[idx2++]
                );
    }
    while (idx1 <= mid)
        cur.push_back(in[idx1++]);
    while (idx2 <= right)
        cur.push_back(in[idx2++]);
    for (size_t i = 0; i < cur.size(); ++i) {
        in[i + left] = cur[i];
    }
}

/**
 * sort vector
 * @tparam T            vector value type
 * @tparam Cmp          compare function type
 * @param in            input vector<T>
 * @param left          start index
 * @param right         end index
 * @param fun           compare function, should return bool
 */
template<typename T, typename Cmp>
void sort(std::vector<T>& in, size_t left, size_t right, Cmp& fun) {
    if (left >= right)
        return;
    size_t mid = (left + right) >> 1;
    sort(in, left, mid, fun);
    sort(in, mid+1, right, fun);
    merge(in, left, mid, right, fun);
}

template<typename T, typename Cmp = std::function<bool(T, T)>>
void sort(std::vector<T>& in, Cmp fun = ::std::less<T>()) {
    if (in.size() < 2)
        return;
    sort(in, 0, in.size() - 1, fun);
}