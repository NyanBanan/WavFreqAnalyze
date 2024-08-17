//
// Created by nyanbanan on 17.08.24.
//

#include "FmtChunk.hpp"

namespace wav::chunk {
    FmtChunk::FmtChunk(chunk_size_t chunk_size) : Chunk(chunk_id, chunk_size) {}

    FmtChunk::FormatTag FmtChunk::getFormatTag() const {
        return _format_tag;
    }

    void FmtChunk::setFormatTag(FmtChunk::FormatTag formatTag) {
        _format_tag = formatTag;
    }

    uint16_t FmtChunk::getChannels() const {
        return _channels;
    }

    void FmtChunk::setChannels(uint16_t channels) {
        _channels = channels;
    }

    uint32_t FmtChunk::getSamplesPerSec() const {
        return _samples_per_sec;
    }

    void FmtChunk::setSamplesPerSec(uint32_t samplesPerSec) {
        _samples_per_sec = samplesPerSec;
    }

    uint32_t FmtChunk::getAvgBytesPerSec() const {
        return _avg_bytes_per_sec;
    }

    void FmtChunk::setAvgBytesPerSec(uint32_t avgBytesPerSec) {
        _avg_bytes_per_sec = avgBytesPerSec;
    }

    uint16_t FmtChunk::getBlockAlign() const {
        return _block_align;
    }

    void FmtChunk::setBlockAlign(uint16_t blockAlign) {
        _block_align = blockAlign;
    }

    uint16_t FmtChunk::getBitsPerSample() const {
        return _bits_per_sample;
    }

    void FmtChunk::setBitsPerSample(uint16_t bitsPerSample) {
        _bits_per_sample = bitsPerSample;
    }

    uint16_t FmtChunk::getExtSize() const {
        return _ext_size;
    }

    void FmtChunk::setExtSize(uint16_t extSize) {
        _ext_size = extSize;
    }

    uint16_t FmtChunk::getValidBitsPerSample() const {
        return _valid_bits_per_sample;
    }

    void FmtChunk::setValidBitsPerSample(uint16_t validBitsPerSample) {
        _valid_bits_per_sample = validBitsPerSample;
    }

    uint32_t FmtChunk::getChannelMask() const {
        return _channel_mask;
    }

    void FmtChunk::setChannelMask(uint32_t channelMask) {
        _channel_mask = channelMask;
    }

    uint64_t FmtChunk::getSubFormat() const {
        return _sub_format;
    }

    void FmtChunk::setSubFormat(uint64_t subFormat) {
        _sub_format = subFormat;
    }

}    //namespace wav::chunk
