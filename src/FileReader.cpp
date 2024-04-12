#include <fstream>

#include "FileReader.h"
#include "ByteUtils.h"

FileReader::FileReader(const std::string& inputFilePath) :
    inputFilePath(inputFilePath) {
    std::ifstream input(inputFilePath, std::ios::binary);
    this->byteBuffer = make_unique<vector<uint8_t>>(
        vector<uint8_t>(std::istreambuf_iterator(input), {})
    );
}

void FileReader::read() const {
    readTotalFileSize();
    readRIFFChunkDescriptor();
    readFmtSubChunk();
    readDataSubChunk();
}

void FileReader::readRIFFChunkDescriptor() const {
    cout << "========== RIFF chunk descriptor ==========" << endl;
    cout << "RIFF chunk descriptor ChunkID: "
        << readBytesAsString(*this->byteBuffer, 0, 4)
        << endl;

    cout << "RIFF chunk descriptor ChunkSize: "
        << read2BytesAsInt(*this->byteBuffer, 4) << endl;

    cout << "RIFF chunk descriptor Format: "
        << readBytesAsString(*this->byteBuffer, 8, 4)
        << endl << endl;
}

void FileReader::readFmtSubChunk() const {
    cout << "============== fmt sub-chunk ==============" << endl;
    cout << "fmt sub-chunk SubChunk1ID: " << readBytesAsString(
            *this->byteBuffer,
            12,
            3
        )
        << endl;

    cout << "fmt sub-chunk SubChunk1Size: "
        << read4BytesAsInt(*this->byteBuffer, 16)
        << endl;

    cout << "fmt sub-chunk AudioFormat: "
        << read2BytesAsInt(*this->byteBuffer, 20)
        << endl;

    cout << "fmt sub-chunk NumChannels: "
        << read2BytesAsInt(*this->byteBuffer, 22)
        << endl;

    cout << "fmt sub-chunk SampleRate: "
        << read4BytesAsInt(*this->byteBuffer, 24)
        << " Hz"
        << endl;

    const int bytesPerSecond = read4BytesAsInt(*this->byteBuffer, 28);
    cout << "fmt sub-chunk ByteRate: " << bytesPerSecond << " bytes/second ("
        << static_cast<float>(bytesPerSecond) * 8.0f / 1000.0f
        << " Kilobits/second)"
        << endl;

    cout << "fmt sub-chunk BlockAlign: "
        << read2BytesAsInt(*this->byteBuffer, 32)
        << endl;

    cout << "fmt sub-chunk BitsPerSample: "
        << read2BytesAsInt(*this->byteBuffer, 34)
        << endl << endl;
}

void FileReader::readTotalFileSize() const {
    cout << "Total file size: " << this->byteBuffer->size()
        << " Bytes ("
        << floorf((static_cast<float>(this->byteBuffer->size()) / 1'000'000.0f) * 100) /
        100
        << " MB)"
        << endl << endl;
}

void FileReader::readDataSubChunk() const {
    cout << "============= data sub-chunk ==============" << endl;
    cout << "data sub-chunk SubChunk2ID: " << readBytesAsString(
            *this->byteBuffer,
            36,
            4
        )
        << endl;

    cout << "data sub-chunk SubChunk2Size: "
        << read4BytesAsInt(*this->byteBuffer, 40)
        << endl;
}
