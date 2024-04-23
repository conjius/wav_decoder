#include <fstream>

#include "FileReader.hpp"
#include "ByteUtils.hpp"
#include "Converter.hpp"
#include "FileReaderReadResult.hpp"
#include "logger/Logger.hpp"

FileReader::FileReader(const std::string& inputFilePath) :
    inputFilePath(inputFilePath) {
    std::ifstream input(inputFilePath, std::ios::binary);
    this->byteBuffer = make_unique<vector<uint8_t>>(
        vector<uint8_t>(std::istreambuf_iterator(input), {})
    );
}

string FileReader::readRiffChunkDescriptorChunkId() const {
    const auto riffChunkDescriptorChunkId =
        readBytesAsString(*this->byteBuffer, 0, 4);
    spdlog::info("RIFF chunk descriptor ChunkID: {}", riffChunkDescriptorChunkId);
    return riffChunkDescriptorChunkId;
}

size_t FileReader::readRiffChunkDescriptorChunkSize() const {
    const auto riffChunkDescriptorChunkSize = read2BytesAsInt(*this->byteBuffer, 4);
    spdlog::info("RIFF chunk descriptor ChunkSize: {}", riffChunkDescriptorChunkSize);
    return riffChunkDescriptorChunkSize;
}

string FileReader::readRiffChunkDescriptorFormat() const {
    const auto riffChunkDescriptorFormat = readBytesAsString(*this->byteBuffer, 8, 4);
    spdlog::info("RIFF chunk descriptor Format: {}", riffChunkDescriptorFormat);
    return riffChunkDescriptorFormat;
}

string FileReader::readFmtSubChunk1Id() const {
    const auto fmtSubChunk1Id = readBytesAsString(
        *this->byteBuffer,
        12,
        3
    );
    spdlog::info("fmt sub-chunk SubChunk1ID: {}", fmtSubChunk1Id);
    return fmtSubChunk1Id;
}

size_t FileReader::readFmtSubChunk1Size() const {
    const auto fmtSubChunk1Size = read4BytesAsInt(*this->byteBuffer, 16);
    spdlog::info("fmt sub-chunk SubChunk1Size: {}", std::to_string(fmtSubChunk1Size));
    return fmtSubChunk1Size;
}

int FileReader::readFmtSubChunkAudioFormat() const {
    const auto fmtSubChunkAudioFormat = read2BytesAsInt(*this->byteBuffer, 20);
    spdlog::info("fmt sub-chunk AudioFormat: {}", fmtSubChunkAudioFormat);
    return fmtSubChunkAudioFormat;
}

int FileReader::readFmtSubChunkNumChannels() const {
    const auto fmtSubChunkNumChannels = read2BytesAsInt(*this->byteBuffer, 22);
    spdlog::info("fmt sub-chunk NumChannels: {}", fmtSubChunkNumChannels);
    return fmtSubChunkNumChannels;
}

int FileReader::readFmtSubChunkSampleRate() const {
    const auto fmtSubChunkSampleRate = read4BytesAsInt(*this->byteBuffer, 24);
    spdlog::info("fmt sub-chunk SampleRate: {} Hz", fmtSubChunkSampleRate);
    return fmtSubChunkSampleRate;
}

int FileReader::readFmtSubChunkByteRate() const {
    const int ByteRate = read4BytesAsInt(*this->byteBuffer, 28);
    spdlog::info(
        "fmt sub-chunk ByteRate: {} bytes/second ({} Kilobits/second)",
        ByteRate, Converter::byteRateToKiloBitRate(ByteRate)
    );
    return ByteRate;
}

size_t FileReader::readFmtSubChunkBlockAlign() const {
    const auto fmtSubChunkBlockAlign = read2BytesAsInt(*this->byteBuffer, 32);
    spdlog::info("fmt sub-chunk BlockAlign: {}", fmtSubChunkBlockAlign);
    return fmtSubChunkBlockAlign;
}

int FileReader::readFmtSubChunkBitsPerSample() const {
    const auto bitsPerSample = read2BytesAsInt(*this->byteBuffer, 34);
    spdlog::info("fmt sub-chunk BitsPerSample: {}", bitsPerSample);
    return bitsPerSample;
}

string FileReader::readDataSubChunk2Id() const {
    const auto dataSubChunk2Id = readBytesAsString(
        *this->byteBuffer,
        36,
        4
    );
    spdlog::info("data sub-chunk SubChunk2ID: {}", dataSubChunk2Id);
    return dataSubChunk2Id;
}

size_t FileReader::readDataSubChunk2Size() const {
    const auto dataSubChunk2Size = read4BytesAsInt(*this->byteBuffer, 40);
    spdlog::info("data sub-chunk SubChunk2Size: {}", dataSubChunk2Size);
    return dataSubChunk2Size;
}

DataView FileReader::generateDataView(
    const size_t bufferOffset,
    const size_t dataSubChunk2Size
) const {
    const auto dataView = *this->byteBuffer
        | std::views::drop(bufferOffset)
        | std::views::take(dataSubChunk2Size);
    return dataView;
}

FileReaderReadResult FileReader::read() {
    const auto totalFileSizeBytes = readTotalFileSizeBytes();

    spdlog::info("========== RIFF chunk descriptor ==========");
    const auto riffChunkDescriptorChunkId = readRiffChunkDescriptorChunkId();
    const auto riffChunkDescriptorChunkSize = readRiffChunkDescriptorChunkSize();
    const auto riffChunkDescriptorFormat = readRiffChunkDescriptorFormat();

    spdlog::info("============== fmt sub-chunk ==============");
    const auto fmtSubChunk1Id = readFmtSubChunk1Id();
    const auto fmtSubChunk1Size = readFmtSubChunk1Size();
    const auto fmtSubChunkAudioFormat = readFmtSubChunkAudioFormat();
    const auto fmtSubChunkNumChannels = readFmtSubChunkNumChannels();
    const auto fmtSubChunkSampleRate = readFmtSubChunkSampleRate();
    const auto fmtSubChunkByteRate = readFmtSubChunkByteRate();
    const auto fmtSubChunkBlockAlign = readFmtSubChunkBlockAlign();
    const auto fmtSubChunkBitsPerSample = readFmtSubChunkBitsPerSample();

    spdlog::info("============= data sub-chunk ==============");
    const auto dataSubChunk2Id = readDataSubChunk2Id();
    const auto dataSubChunk2Size = readDataSubChunk2Size();
    const auto data = generateDataView(
        44,
        dataSubChunk2Size
    );

    auto fileReaderReadResult = FileReaderReadResult{
        this->byteBuffer,
        totalFileSizeBytes,
        riffChunkDescriptorChunkId,
        riffChunkDescriptorChunkSize,
        riffChunkDescriptorFormat,
        fmtSubChunk1Id,
        fmtSubChunk1Size,
        fmtSubChunkAudioFormat,
        fmtSubChunkNumChannels,
        fmtSubChunkSampleRate,
        fmtSubChunkByteRate,
        fmtSubChunkBlockAlign,
        fmtSubChunkBitsPerSample,
        dataSubChunk2Id,
        dataSubChunk2Size,
        data
    };

    return fileReaderReadResult;
}

size_t FileReader::readTotalFileSizeBytes() const {
    const size_t totalFileSizeBytes = this->byteBuffer->size();
    spdlog::info(
        "Total file size: {} Bytes ({} MB)", totalFileSizeBytes,
        floorf((static_cast<float>(totalFileSizeBytes) / 1'000'000.0f) * 100) / 100
    );
    return totalFileSizeBytes;
}
