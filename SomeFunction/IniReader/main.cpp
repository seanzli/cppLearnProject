#include <iostream>

#include "./iniReader.hpp"

int main() {
    IniReader reader("../data/test.ini");
    reader.getTree();
    return 0;
}