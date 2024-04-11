#pragma once
#include <iostream>

using std::cout, std::endl, std::vector;


class Reader {
    static void readRIFFChunkDescriptor(const vector<uint8_t>& byteBuffer);

    static void readFmtSubChunk(const vector<uint8_t>& byteBuffer);

    static void readTotalFileSize(const vector<uint8_t>& byteBuffer);

    static void readDataSubChunk(const vector<uint8_t>& byteBuffer);
};
