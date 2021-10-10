#include "iniReader.hpp"

#include <iostream>
#include <fstream>

void IniReader::decodeFile(const std::string& ini_file) {
    std::ifstream fin(ini_file);

    // can not open
    if (!fin) {
        this->g_error = ErrorType::FILE_CANNOT_OPEN;
        return;
    }

    // read line by line
    std::string line;
    while (getline(fin, line)) {
        
    }
}