//
// Created by nyanbanan on 17.08.24.
//

#ifndef WAVEANALYSE_CHUNK_HPP
#define WAVEANALYSE_CHUNK_HPP

#include <cstdint>
#include <string>

namespace wav::chunk {

    using chunk_size_t = uint32_t;
    using chunk_id_t = uint32_t;

    //Chunk id is a 4 byte string, this function is designed to conveniently convert this string into a 4 byte number
    //Can be used by other classes to determine the type of chunk
    constexpr chunk_id_t idFromString(const char* const id_str) {
        return chunk_id_t((id_str[0] << 24) + (id_str[1] << 16) + (id_str[2] << 8) + id_str[3]);
    }

    class Chunk {
    public:
        Chunk(chunk_id_t id, chunk_size_t size);

        virtual ~Chunk() = default;

        chunk_id_t id() const;
        chunk_size_t size() const;
        //deserialize method must deserialize chunk data from stream except chunk id and chunk size, this params must be set on chunk construction
        virtual void deserialize(std::istream& data_stream) = 0;

    private:
        chunk_size_t _size;
        chunk_id_t _id;
    };

}    //namespace wav::chunk

#endif    //WAVEANALYSE_CHUNK_HPP
