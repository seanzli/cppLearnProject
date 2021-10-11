#include "iniReader.hpp"

#include <iostream>
#include <fstream>

void IniReader::decodeFile(const std::string& ini_file) {
    std::ifstream fin(ini_file);

    // can not open
    if (!fin) {
        this->g_error = ErrorType::FILE_CANNOT_OPEN;
        std::cout << "cannot open file\n";
        return;
    }

    // read line by line
    std::string cur_protocol_str = "";
    std::string line;
    std::string key;
    while (getline(fin, line)) { ///TODO use interpreter to parse string line
        std::string value;
        int idx = 0;
        int flag = 0;
        while ((flag = decodeLine(line, idx, value)) > 0) {
            switch (flag) {
            case 1 : cur_protocol_str = value; break;
            case 2 : key = value; break;
            case 3 : this->hash[cur_protocol_str][key] = value; break;
            }
        }
    }
}

/**
 * @brief decodeLine
 *                  1> not suppose multi-line
 *                  2> [protocol] should at the beginning of the line
 *                  3> protocol should be surround by []
 *                  4> key should at the left side of =
 *                  5> value should at the right side of =
 *                  6> comment start with ';'
 * 
 * @param line      i  <string&> input line
 * @param idx       io <int&>    decode line index
 * @param value     o  <string&> output value
 * @return int      -1 = error
 *                  0  = end of line
 *                  1  = value is protocol
 *                  2  = value is key
 *                  3  = value is value
 */
int IniReader::decodeLine(std::string& line, int& idx, std::string& value) {
    // delete beginning space
    value = "";
    while (idx < line.size() && line[idx] == ' ')
        ++idx;

    if (idx == line.size())
        return 0;

    if (line[idx] == '[') { // protocol
        return decodeProtocol(line, idx, value);
    } else if (line[idx] == ';') // comment
        return 0;
    else if (line[idx] == '=')  { // value
        return decodeValue(line, idx, value);
    } else { // key
        return decodeKey(line, idx, value);
    }
    return -1;
}

int IniReader::decodeProtocol(std::string &line, int &idx, std::string &value) {
    ++idx;
    while (idx < line.size() && line[idx] != ']')
        value.push_back(line[idx++]);

    if (line[idx] == ']') { // find protocol end sign
        ++idx;
        return 1;
    } else {
        return -1;
    }
    return -1;
}
int IniReader::decodeValue(std::string &line, int &idx, std::string &value) {
    ++idx;
    while (idx < line.size() && line[idx] == ' ') // delete front space
        ++idx;
    while (idx < line.size() && line[idx] != ';')
        value.push_back(line[idx++]);
    while (value.size() && value.back() == ' ') // delete end space
        value.pop_back();
    return 3;
}

int IniReader::decodeKey(std::string &line, int &idx, std::string &value) {
    while (idx < line.size() && line[idx] == ' ') // delete front space
        ++idx;
    while (idx < line.size() && line[idx] != '=') 
        value.push_back(line[idx++]);
    if (line[idx] == '=') {
        while (value.size() && value.back() == ' ') // delete end space
            value.pop_back();
        return 2;
    }
    return -1;
}

void IniReader::getProtocolList() {
    std::cout << "========\n";
    for (auto itr = hash.begin(); itr != hash.end(); ++itr) {
        std::cout << itr->first << std::endl;
    }
}

void IniReader::getTree() {
    std::cout << "========\n";
    for (auto itr = hash.begin(); itr != hash.end(); ++itr) {
        std::cout << "[" << itr->first << "]" << std::endl;
        for (auto key = (*itr).second.begin();
                 key != (*itr).second.end(); ++key) {
            std::cout << key->first << "=" << key->second << "\n";
        }
    }
}