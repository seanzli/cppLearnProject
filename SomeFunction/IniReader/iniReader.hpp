/**
 * @file iniReader.hpp
 * @author Sean 
 * @brief 
 * @version 0.1
 * @date 2021-10-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <string>
#include <unordered_map>

enum class ErrorType{
    NO_ERROR,
    FILE_CANNOT_OPEN,
};

class IniReader {
    // string -> map;
    // map -> string, string
    using Container = std::unordered_map<std::string, 
                      std::unordered_map<std::string, std::string>>;
public:
    IniReader(const std::string& ini_file) {
        g_error = ErrorType::NO_ERROR;
        decodeFile(ini_file);
    }
    ~IniReader(){}

    bool isValid() {return g_error == ErrorType::NO_ERROR;}
    bool getValue(const std::string& key, const std::string& key2
                  std::string& value) {
        value = "";
        auto itr = hash.find(key);
        if (itr == hash.end())
            return false;
        auto itr2 = (itr->second).find(key2);
        if (itr2 == (itr->second).end())
            return false;
        value = itr2->second;
        return true;
    }

// member value
private:
    ErrorType g_error;
    Container hash; // key -> value;

// member function
private:
    void decodeFile(const std::string& ini_file);
};