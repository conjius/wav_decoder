#pragma once
#include <cstdint>
#include <vector>
#include <ranges>

using std::vector, std::unique_ptr, std::string, std::ranges::drop_view,
    std::ranges::ref_view, std::ranges::take_view;

class FileReaderReadResult {
public:
    FileReaderReadResult(
        unique_ptr<vector<uint8_t>>& byteBuffer,
        const size_t& totalFileSizeBytes,
        string riffChunkDescriptorChunkId,
        const size_t& riffChunkDescriptorChunkSize,
        string riffChunkDescriptorFormat,
        string fmtSubChunk1Id,
        const size_t& fmtSubChunk1Size,
        const int& fmtSubChunkAudioFormat,
        const int& fmtSubChunkNumChannels,
        const int& fmtSubChunkSampleRate,
        const int& fmtSubChunkByteRate,
        const size_t& fmtSubChunkBlockAlign,
        const int& fmtSubChunkBitsPerSample,
        string dataSubChunk2Id,
        const size_t& dataSubChunk2Size,
        const take_view<drop_view<ref_view<std::vector<uint8_t>>>>& data
    ) :
        byteBuffer(byteBuffer),
        totalFileSizeBytes(totalFileSizeBytes),
        riffChunkDescriptorChunkId(std::move(riffChunkDescriptorChunkId)),
        riffChunkDescriptorChunkSize(riffChunkDescriptorChunkSize),
        riffChunkDescriptorFormat(std::move(riffChunkDescriptorFormat)),
        fmtSubChunk1Id(std::move(fmtSubChunk1Id)),
        fmtSubChunk1Size(fmtSubChunk1Size),
        fmtSubChunkAudioFormat(fmtSubChunkAudioFormat),
        fmtSubChunkNumChannels(fmtSubChunkNumChannels),
        fmtSubChunkSampleRate(fmtSubChunkSampleRate),
        fmtSubChunkByteRate(fmtSubChunkByteRate),
        fmtSubChunkBlockAlign(fmtSubChunkBlockAlign),
        fmtSubChunkBitsPerSample(fmtSubChunkBitsPerSample),
        dataSubChunk2Id(std::move(dataSubChunk2Id)),
        dataSubChunk2Size(dataSubChunk2Size),
        data(data) {
    }

    unique_ptr<vector<uint8_t>>& byteBuffer;
    size_t totalFileSizeBytes;

    string riffChunkDescriptorChunkId;
    size_t riffChunkDescriptorChunkSize;
    string riffChunkDescriptorFormat;

    string fmtSubChunk1Id;
    size_t fmtSubChunk1Size;
    int fmtSubChunkAudioFormat;
    int fmtSubChunkNumChannels;
    int fmtSubChunkSampleRate;
    int fmtSubChunkByteRate;
    size_t fmtSubChunkBlockAlign;
    int fmtSubChunkBitsPerSample;

    string dataSubChunk2Id;
    size_t dataSubChunk2Size{};

    take_view<drop_view<ref_view<vector<uint8_t>>>> data;
};
