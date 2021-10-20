#include "DecodeFactory.hpp"

#include <typeinfo>
#include <iostream>

int main() {
    auto decoder = Factory::getDecoder(DecoderType::NOVATEL);

    std::cout << typeid(decoder).name() << std::endl;
    
    return 0;
}