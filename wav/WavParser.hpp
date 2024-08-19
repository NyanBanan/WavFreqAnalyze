//
// Created by nyanbanan on 18.08.24.
//

#ifndef WAVEANALYSE_WAVPARSER_HPP
#define WAVEANALYSE_WAVPARSER_HPP

#include <expected>
#include <filesystem>
#include <fstream>

#include "chunk/RIFFChunk.hpp"

namespace wav {

    enum class ParseErrorCode : uint8_t {
        NONE,
        FILE_NOT_EXIST,
        IS_A_DIR,
        WRONG_FILE_FORMAT,
        OPEN_STREAM_ERROR,
        WRONG_FIRST_BLOCK_TYPE
    };

    //method return raw pointer, user is responsible for memory cleaning
    auto parseFile(const std::filesystem::path& filepath) -> std::expected<chunk::RIFFChunk*, ParseErrorCode>;
}    //namespace wav

#endif    //WAVEANALYSE_WAVPARSER_HPP
