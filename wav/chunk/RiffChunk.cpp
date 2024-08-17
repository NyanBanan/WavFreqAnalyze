//
// Created by nyanbanan on 17.08.24.
//

#include "RiffChunk.hpp"

namespace wav::chunk {

    RIFFChunk::RIFFChunk(chunk_size_t chunk_size) : Chunk(chunk_id, chunk_size), _sub_chunks_size(chunk_size - 4) {}

    void RIFFChunk::addSubChunk(const Chunk& chunk) {
        if (auto iter = _sub_chunks.find(chunk.id()); iter != _sub_chunks.end()) {
            iter->second = chunk;
        } else {
            _sub_chunks.emplace(chunk.id(), chunk);
        }
    }

    void RIFFChunk::addSubChunk(Chunk&& chunk) {
        if (auto iter = _sub_chunks.find(chunk.id()); iter != _sub_chunks.end()) {
            iter->second = chunk;
        } else {
            _sub_chunks.emplace(chunk.id(), chunk);
        }
    }

    std::optional<FmtChunk*> RIFFChunk::getFmtChunk() {}

}    //namespace wav::chunk
