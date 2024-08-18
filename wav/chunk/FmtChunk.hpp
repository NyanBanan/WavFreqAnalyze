//
// Created by nyanbanan on 17.08.24.
//

#ifndef WAVEANALYSE_FMTCHUNK_HPP
#define WAVEANALYSE_FMTCHUNK_HPP

#include <istream>

#include "Chunk.hpp"

namespace wav::chunk {

    class FmtChunk : public Chunk {
    public:
        enum class FormatTag : uint16_t {
            PCM = 0x0001,
            IEEE_FLOAT = 0x0003,
            ALAW = 0x0006,
            MULAW = 0x0007,
            EXTENSIBLE = 0xFFFE
        };

        static constexpr std::string_view id_str{"fmt "};
        static constexpr chunk_id_t chunk_id = {idFromString(id_str.data())};

        //Create an empty fmt chunk with invalid params
        //Required to set param fields by using setters
        FmtChunk(chunk_size_t chunk_size);

        FormatTag getFormatTag() const;
        uint16_t getChannels() const;
        uint32_t getSamplesPerSec() const;
        uint32_t getAvgBytesPerSec() const;
        uint16_t getBlockAlign() const;
        uint16_t getBitsPerSample() const;
        uint16_t getExtSize() const;
        uint16_t getValidBitsPerSample() const;
        uint32_t getChannelMask() const;
        uint64_t getSubFormat() const;

        void deserialize(std::istream& data_stream) override;

    private:
        FormatTag _format_tag;
        uint16_t _channels{};
        uint32_t _samples_per_sec{};
        uint32_t _avg_bytes_per_sec{};
        uint16_t _block_align{};
        uint16_t _bits_per_sample{};
        uint16_t _ext_size{};
        uint16_t _valid_bits_per_sample{};
        uint32_t _channel_mask{};
        uint64_t _sub_format{};
    };

}    //namespace wav::chunk
#endif    //WAVEANALYSE_FMTCHUNK_HPP
