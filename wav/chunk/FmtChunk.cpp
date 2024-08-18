//
// Created by nyanbanan on 17.08.24.
//

#include "FmtChunk.hpp"

namespace wav::chunk {
    FmtChunk::FmtChunk(chunk_size_t chunk_size) : Chunk(chunk_id, chunk_size) {}

    FmtChunk::FormatTag FmtChunk::getFormatTag() const {
        return _format_tag;
    }

    uint16_t FmtChunk::getChannels() const {
        return _channels;
    }

    uint32_t FmtChunk::getSamplesPerSec() const {
        return _samples_per_sec;
    }

    uint32_t FmtChunk::getAvgBytesPerSec() const {
        return _avg_bytes_per_sec;
    }

    uint16_t FmtChunk::getBlockAlign() const {
        return _block_align;
    }

    uint16_t FmtChunk::getBitsPerSample() const {
        return _bits_per_sample;
    }

    uint16_t FmtChunk::getExtSize() const {
        return _ext_size;
    }

    uint16_t FmtChunk::getValidBitsPerSample() const {
        return _valid_bits_per_sample;
    }

    uint32_t FmtChunk::getChannelMask() const {
        return _channel_mask;
    }

    uint64_t FmtChunk::getSubFormat() const {
        return _sub_format;
    }

    void FmtChunk::deserialize(std::istream& data_stream) {
        data_stream.read(reinterpret_cast<char*>(&_format_tag), 2);
        data_stream.read(reinterpret_cast<char*>(&_channels), 2);
        data_stream.read(reinterpret_cast<char*>(&_samples_per_sec), 4);
        data_stream.read(reinterpret_cast<char*>(&_avg_bytes_per_sec), 4);
        data_stream.read(reinterpret_cast<char*>(&_block_align), 2);
        data_stream.read(reinterpret_cast<char*>(&_bits_per_sample), 2);
        if (size() == 18) {
            data_stream.read(reinterpret_cast<char*>(&_ext_size), 2);
        }
        if (size() == 40 && _ext_size == 22) {
            data_stream.read(reinterpret_cast<char*>(&_valid_bits_per_sample), 2);
            data_stream.read(reinterpret_cast<char*>(&_channel_mask), 4);
            data_stream.read(reinterpret_cast<char*>(&_sub_format), 16);
        }
    }

}    //namespace wav::chunk
