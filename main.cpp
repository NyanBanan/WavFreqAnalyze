#include <iostream>

#include "wav/WavParser.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << std::format("usage :{} 'path to .wav/.wave file'", __FILE_NAME__);
    }

    std::filesystem::path filepath(argv[1]);
    auto core_chunk = wav::parseFile(filepath);

    return 0;
}
