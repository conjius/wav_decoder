#pragma once
#include <iostream>

#include "FileReaderReadResult.hpp"

using std::cout, std::endl, std::vector, std::string, std::unique_ptr, std::make_unique;
using DataView = take_view<drop_view<ref_view<vector<uint8_t>>>>;

class FileReader {
public:
    explicit FileReader(const std::string& inputFilePath);

    [[nodiscard]] FileReaderReadResult read();

private:
    [[nodiscard]] size_t readTotalFileSizeBytes() const;
    [[nodiscard]] string readRiffChunkDescriptorChunkId() const;
    [[nodiscard]] size_t readRiffChunkDescriptorChunkSize() const;
    [[nodiscard]] string readRiffChunkDescriptorFormat() const;
    [[nodiscard]] string readFmtSubChunk1Id() const;
    [[nodiscard]] size_t readFmtSubChunk1Size() const;
    [[nodiscard]] int readFmtSubChunkAudioFormat() const;
    [[nodiscard]] int readFmtSubChunkNumChannels() const;
    [[nodiscard]] int readFmtSubChunkSampleRate() const;
    [[nodiscard]] int readFmtSubChunkByteRate() const;
    [[nodiscard]] size_t readFmtSubChunkBlockAlign() const;
    [[nodiscard]] int readFmtSubChunkBitsPerSample() const;
    [[nodiscard]] string readDataSubChunk2Id() const;
    [[nodiscard]] size_t readDataSubChunk2Size() const;
    [[nodiscard]] DataView generateDataView(
        size_t bufferOffset,
        size_t dataSubChunk2Size
    ) const;

    const string& inputFilePath;
    unique_ptr<vector<uint8_t>> byteBuffer;
};
