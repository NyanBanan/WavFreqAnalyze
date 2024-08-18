//
// Created by nyanbanan on 17.08.24.
//

#include "RIFFChunk.hpp"

namespace wav::chunk {

    RIFFChunk::RIFFChunk(chunk_size_t chunk_size) : Chunk(chunk_id, chunk_size), _sub_chunks_size(size() - 4) {}

    void RIFFChunk::addSubChunk(Chunk* chunk) {
        if (auto iter = _sub_chunks.find(chunk->id()); iter != _sub_chunks.end()) {
            iter->second.reset(chunk);
        } else {
            _sub_chunks.emplace(chunk->id(), chunk);
        }
        chunk = nullptr;
    }

    std::optional<std::shared_ptr<FmtChunk>> RIFFChunk::getFmtChunk() {
        auto iter = _sub_chunks.find(FmtChunk::chunk_id);
        //find is guaranteed that iter contains FmtChunk, that's why I call static cast
        return iter != _sub_chunks.end() ? std::optional(std::static_pointer_cast<wav::chunk::FmtChunk>(iter->second))
                                         : std::nullopt;
    }

    std::optional<std::shared_ptr<DataChunk>> RIFFChunk::getDataChunk() {
        auto iter = _sub_chunks.find(DataChunk::chunk_id);
        //find is guaranteed that iter contains DataChunk, that's why I call static cast
        return iter != _sub_chunks.end() ? std::optional(std::static_pointer_cast<DataChunk>(iter->second))
                                         : std::nullopt;
    }

    void RIFFChunk::deserialize(std::istream& data_stream) {
        //static array for read wave id from stream
        static char wave_id[4];
        data_stream.read(wave_id, 4);
        while (true) {
            char next_chunk_id_str[4];
            data_stream.read(next_chunk_id_str, 4);

            if (data_stream.eof()) {
                break;
            }

            chunk_id_t next_chunk_size{0};
            data_stream.read(reinterpret_cast<char*>(&next_chunk_size), 4);

            auto next_chunk_id = chunk::idFromString(next_chunk_id_str);

            switch (next_chunk_id) {
                case FmtChunk::chunk_id: {
                    auto new_chunk = new FmtChunk(next_chunk_size);
                    new_chunk->deserialize(data_stream);
                    addSubChunk(new_chunk);
                    break;
                }
                case DataChunk::chunk_id: {
                    auto new_chunk = new DataChunk(next_chunk_size);
                    new_chunk->deserialize(data_stream);
                    addSubChunk(new_chunk);
                    break;
                }
                default: {
                    std::cout << std::format("Unknown chunk id. Str: {:s}, Id: {} \n", next_chunk_id_str, next_chunk_id);
                    data_stream.seekg(next_chunk_size + 1, std::ios_base::cur);
                }
            }
        }
    }

}    //namespace wav::chunk
