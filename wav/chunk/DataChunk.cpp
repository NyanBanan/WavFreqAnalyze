//
// Created by nyanbanan on 17.08.24.
//

#include "DataChunk.hpp"

namespace wav::chunk {

    DataChunk::DataChunk(chunk_size_t chunk_size) : Chunk(chunk_id, chunk_size) {}

    std::shared_ptr<char[]> DataChunk::getSamplesData() const {
        return _samples_data;
    }

    void DataChunk::setSamplesData(const std::shared_ptr<char[]>& samplesData) {
        _samples_data = samplesData;
    }
}    //namespace wav::chunk
