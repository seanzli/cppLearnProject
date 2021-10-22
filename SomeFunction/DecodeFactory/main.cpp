#include "DecodeFactory.hpp"
#include "NovatelSubscribe.hpp"

#include <typeinfo>
#include <iostream>
#include <fstream>

int main(int, char**) {
    
    std::string path = "test.txt";
    std::ifstream in(path, std::ifstream::binary);

    constexpr unsigned int BUFFER_MAX = 1024;
    char temp_buffer[BUFFER_MAX]{};

    if (!in.is_open())
        throw std::runtime_error("File open failure\n");

    Decoder pDecoder;
    std::shared_ptr<DataSubscribe> novatelGet(new NovatelSubscribe());
    pDecoder.attach(DecoderType::NOVATEL, novatelGet);
    Container que;
    while (in.read(temp_buffer, BUFFER_MAX).eof() == false) {
        que.insert(que.end(), temp_buffer, temp_buffer + BUFFER_MAX);
        pDecoder.decode(que);
    }
    
    // std::cout << dynamic_cast<NovatelSubscribe*>(novatelGet.get())->count << std::endl;

    return 0;
}
