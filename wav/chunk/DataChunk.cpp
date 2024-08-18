//
// Created by nyanbanan on 17.08.24.
//

#include "DataChunk.hpp"

#include <iostream>

namespace wav::chunk {

    DataChunk::DataChunk(chunk_size_t chunk_size)
        : Chunk(chunk_id, chunk_size),
          _samples_data(std::make_shared<char[]>(size())) {}

    std::shared_ptr<char[]> DataChunk::getSamplesData() const {
        return _samples_data;
    }

    void DataChunk::deserialize(std::istream& data_stream) {
        data_stream.read(_samples_data.get(), size());
        //read pad byte from stream
        if (size() % 2 != 0) {
            char trash;
            data_stream.read(&trash, 1);
        }
    }
}    //namespace wav::chunk
