//
// Created by nyanbanan on 17.08.24.
//

#ifndef WAVEANALYSE_RIFFCHUNK_HPP
#define WAVEANALYSE_RIFFCHUNK_HPP

#include <format>
#include <iostream>
#include <map>
#include <optional>
#include <ranges>
#include <vector>

#include "Chunk.hpp"
#include "DataChunk.hpp"
#include "FmtChunk.hpp"

namespace wav::chunk {

    class RIFFChunk : public Chunk {
    public:
        static constexpr std::string_view id_str{"RIFF"};
        static constexpr chunk_id_t chunk_id = {idFromString(id_str.data())};

        //Create an empty RIFF chunk with 0 sub chunks
        //Required to add sub chunks by method
        RIFFChunk(chunk_size_t chunk_size);

        //this method take control under chunk data and set nullptr to chunk pointer
        void addSubChunk(Chunk* chunk);

        std::optional<std::shared_ptr<FmtChunk>> getFmtChunk();
        std::optional<std::shared_ptr<DataChunk>> getDataChunk();

        void deserialize(std::istream& data_stream) override;

    private:
        const uint32_t _sub_chunks_size{};
        std::map<chunk_id_t, std::shared_ptr<Chunk>> _sub_chunks;
    };

}    //namespace wav::chunk

#endif    //WAVEANALYSE_RIFFCHUNK_HPP
