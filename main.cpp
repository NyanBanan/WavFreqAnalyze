#include <iostream>

#include "wav/WavParser.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << std::format("usage :{} 'path to .wav/.wave file'", __FILE_NAME__);
    }

    std::filesystem::path filepath(argv[1]);
    auto core_chunk = wav::parseFile(filepath);

    if (!core_chunk.has_value()) {
        switch (core_chunk.error()) {
            case wav::ParseErrorCode::NONE:
                break;
            case wav::ParseErrorCode::FILE_NOT_EXIST: {
                std::cout << "File not exist" << std::endl;
                break;
            }
            case wav::ParseErrorCode::IS_A_DIR:
                std::cout << "Passed path is a directory" << std::endl;
                break;
            case wav::ParseErrorCode::WRONG_FILE_FORMAT:
                std::cout << "File format must be .wav or .wave" << std::endl;
                break;
            case wav::ParseErrorCode::OPEN_STREAM_ERROR:
                std::cout << "Open stream error" << std::endl;
                break;
            case wav::ParseErrorCode::WRONG_FIRST_BLOCK_TYPE:
                std::cout << "File structure wrong" << std::endl;
                break;
            default:
                std::cout << "Unknown error" << std::endl;
        }
        return -1;
    }

    auto fmt_opt = core_chunk.value()->getFmtChunk();

    if(fmt_opt.has_value()){
        std::cout << *fmt_opt.value();
    }

    return 0;
}
