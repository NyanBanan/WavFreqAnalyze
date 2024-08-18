//
// Created by nyanbanan on 17.08.24.
//

#ifndef WAVEANALYSE_DATACHUNK_HPP
#define WAVEANALYSE_DATACHUNK_HPP

#include <istream>
#include <memory>
#include <span>

#include "Chunk.hpp"

namespace wav::chunk {
    class DataChunk : public Chunk {
    public:
        static constexpr std::string_view id_str{"data"};
        static constexpr chunk_id_t chunk_id = {idFromString(id_str.data())};

        //Create an empty data chunk with invalid data
        //Required to set data by using setter
        DataChunk(chunk_size_t chunk_size);

        [[nodiscard]] std::shared_ptr<char[]> getSamplesData() const;

        void deserialize(std::istream& data_stream) override;

    private:
        std::shared_ptr<char[]> _samples_data;
    };
}    //namespace wav::chunk
#endif    //WAVEANALYSE_DATACHUNK_HPP
