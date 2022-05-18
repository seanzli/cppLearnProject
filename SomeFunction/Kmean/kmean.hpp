#pragma once

#include <vector>
#include <cmath>

namespace K_MEAN {
    struct Data {
        double x;
        Data() : x(0.0) {}
        Data(double _x) : x(_x) {}
        Data operator+(const Data& rhs) const {
            return Data(x + rhs.x);
        }
        double operator-(const Data& rhs) const {
            return fabs(x - rhs.x);
        }
        double operator/(const double rhs) const {
            return x / rhs;
        }
    };
    class KMean {
    public:
        KMean(const std::vector<Data>& data, unsigned k = 2)
            : m_data(data), m_k(k) {}

        void run() {
            size_t size = m_data.size();
            if (size <= m_k) {
                for (size_t i = 0; i < size; ++i)
                    result.emplace_back(i);
                return;
            }
            std::vector<Data> center(m_k, 0);
            for (size_t i = 0; i < m_k; ++i)
                center.at(i) = i;
            unsigned iterator = 0;
            while (iterator < max_iterator /*&& not change at last iterator */ ) {
                std::vector<unsigned> cur(size, 0);
                for (size_t i = 0; i < size; ++i) {
                    std::vector<double> dis(m_k, INT_MAX);
                    for (size_t j = 0; j < m_k; ++j) {
                        dis[j] = m_data[i] - center[j];
                    }
                    cur[i] = std::distance(std::min_element(dis.begin(), dis.end()), dis.begin());
                }
                if (cur == result)
                    break;
                result = cur;
                updateCenter(center, result);
            }
        }

        void updateCenter(std::vector<Data>& center, const std::vector<unsigned >& idx) {
            center = std::vector<Data>(m_k);
            std::vector<unsigned> num(m_k, 0);
            size_t size = m_data.size();
            for (size_t i = 0; i < size; ++i) {
                center[idx[i]] = center[idx[i]] + m_data[i];
                ++num[idx[i]];
            }
            for (size_t i = 0; i < m_k; ++i)
                center[i] = center[i] / num[i];
        }

    private:
        const std::vector<Data>& m_data;
        const unsigned m_k;
        std::vector<unsigned > result; // size should as same as data, value = class id;
        unsigned max_iterator = 10;
    };
}