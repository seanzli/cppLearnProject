/**
 * @file readSudo.hpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class readSudo {
public:
    readSudo(std::string file_path) {
        std::ifstream fin(file_path);

        std::string str;

        while (getline(fin, str)) {
            std::vector<int> cur;
            split(str, cur);
            m_data.push_back(cur);
        }
    }

    std::vector<std::vector<int>>& getData() {
        return m_data;
    }    

// member data
private:
    std::vector<std::vector<int>> m_data;

// member method
private:
    void split(const std::string& in, std::vector<int>& out) {
        std::istringstream strstream(in);
        std::string token;
        while (getline(strstream, token, ' ')) {
            out.push_back(std::stoi(token));
        }
    }
};