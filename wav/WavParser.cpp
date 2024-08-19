//
// Created by nyanbanan on 19.08.24.
//

#include "WavParser.hpp"

namespace wav {
    auto parseFile(const std::filesystem::path& filepath) -> std::expected<chunk::RIFFChunk*, ParseErrorCode> {
        if (!exists(filepath)) {
            return std::unexpected<ParseErrorCode>{ParseErrorCode::FILE_NOT_EXIST};
        } else if (is_directory(filepath)) {
            return std::unexpected<ParseErrorCode>{ParseErrorCode::IS_A_DIR};
        } else if (filepath.extension() != ".wav" && filepath.extension() != ".wave") {
            return std::unexpected<ParseErrorCode>{ParseErrorCode::WRONG_FILE_FORMAT};
        }
        std::ifstream read_stream(filepath);

        if (!read_stream.is_open()) {
            return std::unexpected<ParseErrorCode>{ParseErrorCode::OPEN_STREAM_ERROR};
        }

        char next_chunk_id_str[4];
        read_stream.read(next_chunk_id_str, 4);
        wav::chunk::chunk_id_t next_chunk_size{0};
        read_stream.read(reinterpret_cast<char*>(&next_chunk_size), 4);

        auto next_chunk_id = wav::chunk::idFromString(next_chunk_id_str);

        if (next_chunk_id != wav::chunk::RIFFChunk::chunk_id) {
            return std::unexpected<ParseErrorCode>{ParseErrorCode::WRONG_FIRST_BLOCK_TYPE};
        }
        auto core_chunk = new wav::chunk::RIFFChunk(next_chunk_size);
        core_chunk->deserialize(read_stream);
        return core_chunk;
    }
}    //namespace wav
