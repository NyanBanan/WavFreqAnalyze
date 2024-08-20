//
// Created by nyanbanan on 18.08.24.
//

#include "WavFrequencyAnalyze.hpp"

namespace wav {

    static uint32_t samples_num = 0;
    static int channels_num = 0;
    static uint32_t samples_per_sec = 0;
    static std::unique_ptr<int32_t[]> data = nullptr;

    static void analyzeOneChannel(int cur_channel, std::promise<AnalyzeResult> result) {
        uint32_t lowest_samples_per_period = 0;
        uint32_t max_samples_per_period = 0;
        uint32_t samples_per_period = 1;

        bool is_up_direction{true};
        bool is_first_zero_found{false};

        for (auto i = cur_channel; i < samples_num - 1; i += channels_num) {
            samples_per_period++;
            auto curr_sample = data[i];
            auto next_sample = data[i + cur_channel];
            if ((float)(curr_sample * next_sample) <= 0) {
                if (is_first_zero_found) {
                    if ((is_up_direction && next_sample > curr_sample)
                        || (!is_up_direction && next_sample < curr_sample)) {
                        if (samples_per_period < lowest_samples_per_period || lowest_samples_per_period == 0) {
                            lowest_samples_per_period = samples_per_period;
                        }
                        if (samples_per_period > max_samples_per_period || max_samples_per_period == 0) {
                            max_samples_per_period = samples_per_period;
                        }

                        samples_per_period = 0;
                    }
                } else {
                    is_first_zero_found = true;
                    is_up_direction = next_sample > curr_sample;
                }
            }
        }
        auto lowest_period_time = lowest_samples_per_period / (double)samples_per_sec;
        auto max_freq = 1 / lowest_period_time;
        auto max_period_time = max_samples_per_period / (double)samples_per_sec;
        auto lowest_freq = 1 / max_period_time;

        result.set_value({lowest_freq, max_freq});
    }

    std::expected<std::vector<AnalyzeResult>, AnalyzeErrorCode> analyze(chunk::RIFFChunk* core_chunk) {
        auto fmt_opt = core_chunk->getFmtChunk();
        if (!fmt_opt) {
            return std::unexpected<AnalyzeErrorCode>(AnalyzeErrorCode::FMT_CHUNK_REQUIRED);
        }
        auto fmt_chunk = fmt_opt.value();

        auto data_opt = core_chunk->getDataChunk();
        if (!data_opt) {
            return std::unexpected<AnalyzeErrorCode>(AnalyzeErrorCode::DATA_CHUNK_REQUIRED);
        }
        auto data_chunk = data_opt.value();
        channels_num = fmt_chunk->getChannels();
        samples_per_sec = fmt_chunk->getSamplesPerSec();

        std::vector<AnalyzeResult> result;
        result.reserve(channels_num);

        auto bytesPerSample = fmt_chunk->getBitsPerSample() / 8;
        samples_num = data_chunk->size() / bytesPerSample;

        data = std::make_unique<int32_t[]>(samples_num);
        memcpy(data.get(), data_chunk->getSamplesData().get(), data_chunk->size());

        std::vector<std::future<AnalyzeResult>> future_results;

        for (auto cur_channel = 0; cur_channel < channels_num; ++cur_channel) {
            std::promise<AnalyzeResult> cur_promise;
            auto cur_future = cur_promise.get_future();
            std::thread start{analyzeOneChannel, cur_channel, std::move(cur_promise)};
            start.detach();
            future_results.push_back(std::move(cur_future));
        }

        std::ranges::for_each(future_results, [&result](auto& res) {
            result.push_back(res.get());
        });

        return result;
    }
}    //namespace wav
