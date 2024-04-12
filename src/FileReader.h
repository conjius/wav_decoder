#pragma once
#include <iostream>

using std::cout, std::endl, std::vector, std::string, std::unique_ptr, std::make_unique;


class FileReader {
public:
    explicit FileReader(const std::string& inputFilePath);

    void read() const;

private:
    void readRIFFChunkDescriptor() const;

    void readFmtSubChunk() const;

    void readTotalFileSize() const;

    void readDataSubChunk() const;

    const string& inputFilePath;
    unique_ptr<vector<uint8_t>> byteBuffer;
};
