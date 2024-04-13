#include <fstream>

#include "FileReader.hpp"
#include "ByteUtils.hpp"
#include "Converter.h"
#include "FileReaderReadResult.hpp"

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
    cout << "RIFF chunk descriptor ChunkID: " << riffChunkDescriptorChunkId << endl;
    return riffChunkDescriptorChunkId;
}

size_t FileReader::readRiffChunkDescriptorChunkSize() const {
    const auto riffChunkDescriptorChunkSize = read2BytesAsInt(*this->byteBuffer, 4);
    cout << "RIFF chunk descriptor ChunkSize: " << riffChunkDescriptorChunkSize << endl;
    return riffChunkDescriptorChunkSize;
}

string FileReader::readRiffChunkDescriptorFormat() const {
    const auto riffChunkDescriptorFormat = readBytesAsString(*this->byteBuffer, 8, 4);
    cout << "RIFF chunk descriptor Format: " << riffChunkDescriptorFormat << endl << endl;
    return riffChunkDescriptorFormat;
}

string FileReader::readFmtSubChunk1Id() const {
    const auto fmtSubChunk1Id = readBytesAsString(
        *this->byteBuffer,
        12,
        3
    );
    cout << "fmt sub-chunk SubChunk1ID: " << fmtSubChunk1Id << endl;
    return fmtSubChunk1Id;
}

size_t FileReader::readFmtSubChunk1Size() const {
    const auto fmtSubChunk1Size = read4BytesAsInt(*this->byteBuffer, 16);
    cout << "fmt sub-chunk SubChunk1Size: " << fmtSubChunk1Size << endl;
    return fmtSubChunk1Size;
}

int FileReader::readFmtSubChunkAudioFormat() const {
    const auto fmtSubChunkAudioFormat = read2BytesAsInt(*this->byteBuffer, 20);
    cout << "fmt sub-chunk AudioFormat: " << fmtSubChunkAudioFormat << endl;
    return fmtSubChunkAudioFormat;
}

int FileReader::readFmtSubChunkNumChannels() const {
    const auto fmtSubChunkNumChannels = read2BytesAsInt(*this->byteBuffer, 22);
    cout << "fmt sub-chunk NumChannels: " << fmtSubChunkNumChannels << endl;
    return fmtSubChunkNumChannels;
}

int FileReader::readFmtSubChunkSampleRate() const {
    const auto fmtSubChunkSampleRate = read4BytesAsInt(*this->byteBuffer, 24);
    cout << "fmt sub-chunk SampleRate: " << fmtSubChunkSampleRate << " Hz" << endl;
    return fmtSubChunkSampleRate;
}

int FileReader::readFmtSubChunkByteRate() const {
    const int ByteRate = read4BytesAsInt(*this->byteBuffer, 28);
    cout << "fmt sub-chunk ByteRate: " << ByteRate << " bytes/second ("
        << Converter::byteRateToKiloBitRate(ByteRate)
        << " Kilobits/second)"
        << endl;
    return ByteRate;
}

size_t FileReader::readFmtSubChunkBlockAlign() const {
    const auto fmtSubChunkBlockAlign = read2BytesAsInt(*this->byteBuffer, 32);
    cout << "fmt sub-chunk BlockAlign: " << fmtSubChunkBlockAlign << endl;
    return fmtSubChunkBlockAlign;
}

int FileReader::readFmtSubChunkBitsPerSample() const {
    const auto bitsPerSample = read2BytesAsInt(*this->byteBuffer, 34);
    cout << "fmt sub-chunk BitsPerSample: " << bitsPerSample << endl << endl;
    return bitsPerSample;
}

string FileReader::readDataSubChunk2Id() const {
    const auto dataSubChunk2Id = readBytesAsString(
        *this->byteBuffer,
        36,
        4
    );
    cout << "data sub-chunk SubChunk2ID: " << dataSubChunk2Id << endl;
    return dataSubChunk2Id;
}

size_t FileReader::readDataSubChunk2Size() const {
    const auto dataSubChunk2Size = read4BytesAsInt(*this->byteBuffer, 40);
    cout << "data sub-chunk SubChunk2Size: " << dataSubChunk2Size << endl;
    return dataSubChunk2Size;
}

take_view<drop_view<ref_view<vector<uint8_t>>>> FileReader::generateDataView(
    const size_t bufferOffset,
    const size_t dataSubChunk2Size
) const {
    const auto dataView = *this->byteBuffer
        | std::views::drop(dataSubChunk2Size)
        | std::views::take(dataSubChunk2Size);
    return dataView;
}

FileReaderReadResult FileReader::read() {
    auto totalFileSizeBytes = readTotalFileSizeBytes();

    cout << "========== RIFF chunk descriptor ==========" << endl;
    const auto riffChunkDescriptorChunkId = readRiffChunkDescriptorChunkId();
    const auto riffChunkDescriptorChunkSize = readRiffChunkDescriptorChunkSize();
    const auto riffChunkDescriptorFormat = readRiffChunkDescriptorFormat();

    cout << "============== fmt sub-chunk ==============" << endl;
    const auto fmtSubChunk1Id = readFmtSubChunk1Id();
    const auto fmtSubChunk1Size = readFmtSubChunk1Size();
    const auto fmtSubChunkAudioFormat = readFmtSubChunkAudioFormat();
    const auto fmtSubChunkNumChannels = readFmtSubChunkNumChannels();
    const auto fmtSubChunkSampleRate = readFmtSubChunkSampleRate();
    const auto fmtSubChunkByteRate = readFmtSubChunkByteRate();
    const auto fmtSubChunkBlockAlign = readFmtSubChunkBlockAlign();
    const auto fmtSubChunkBitsPerSample = readFmtSubChunkBitsPerSample();

    cout << "============= data sub-chunk ==============" << endl;
    const auto dataSubChunk2Id = readDataSubChunk2Id();
    const auto dataSubChunk2Size = readDataSubChunk2Size();
    const auto data = generateDataView(
        44,
        dataSubChunk2Size
    );

    auto fileReaderReadResult = FileReaderReadResult(
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
    );

    return fileReaderReadResult;
}

size_t FileReader::readTotalFileSizeBytes() const {
    const size_t totalFileSizeBytes = this->byteBuffer->size();
    cout << "Total file size: " << totalFileSizeBytes
        << " Bytes ("
        << floorf(
            (static_cast<float>(totalFileSizeBytes) / 1'000'000.0f) * 100
        ) / 100
        << " MB)"
        << endl << endl;
    return totalFileSizeBytes;
}
