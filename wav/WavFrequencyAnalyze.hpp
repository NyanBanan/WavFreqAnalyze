//
// Created by nyanbanan on 18.08.24.
//

#ifndef WAVEANALYSE_WAVFREQUENCYANALYZE_HPP
#define WAVEANALYSE_WAVFREQUENCYANALYZE_HPP

#include <cstring>
#include <expected>
#include <thread>
#include <algorithm>
#include <future>
#include <utility>

#include "chunk/RIFFChunk.hpp"

namespace wav {

    enum class AnalyzeErrorCode : uint8_t {
        NONE,
        FMT_CHUNK_REQUIRED,
        DATA_CHUNK_REQUIRED,
    };

    struct AnalyzeResult{
        double lowest_freq;
        double max_freq;
    };

    std::expected<std::vector<AnalyzeResult>, AnalyzeErrorCode> analyze(chunk::RIFFChunk* core_chunk);
}
#endif    //WAVEANALYSE_WAVFREQUENCYANALYZE_HPP
