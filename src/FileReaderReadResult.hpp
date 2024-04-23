#pragma once
#include <vector>
#include <ranges>
#include <string>

using std::vector, std::unique_ptr, std::string, std::ranges::drop_view,
    std::ranges::ref_view, std::ranges::take_view;

struct FileReaderReadResult {
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
