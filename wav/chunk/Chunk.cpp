//
// Created by nyanbanan on 17.08.24.
//

#include "Chunk.hpp"

namespace wav::chunk {

    Chunk::Chunk(chunk_id_t id, chunk_size_t size) : _id(id), _size(size) {}

    constexpr chunk_id_t Chunk::id() const {
        return _id;
    }

    constexpr chunk_size_t Chunk::size() const {
        return _size;
    }
}