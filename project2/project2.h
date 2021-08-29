#pragma once

#include <string>

int char2num(const char c);
char num2char(int n);

std::string add(const std::string& add1, const std::string& add2, const unsigned int base);
std::string sub(const std::string& sub1, const std::string& sub2, const unsigned int base);

int stringCompare(const std::string& str1, const std::string& str2);
bool stringValid(const std::string& str, const unsigned int base, const bool bSigned = false);

std::string sum(const std::string& str1, const std::string& str2, const unsigned int base);

unsigned decode_file(const std::string file_path, std::string& add1, std::string& add2);

void changeBase(std::string& str, const int in_base, const int out_base);