#include "Reader.h"
#include "ByteUtils.h"

void Reader::readRIFFChunkDescriptor(const vector<uint8_t>& byteBuffer) {
    cout << "========== RIFF chunk descriptor ==========" << endl;
    cout << "RIFF chunk descriptor ChunkID: "
        << readBytesAsString(byteBuffer, 0, 4)
        << endl;

    cout << "RIFF chunk descriptor ChunkSize: "
        << read2BytesAsInt(byteBuffer, 4) << endl;

    cout << "RIFF chunk descriptor Format: "
        << readBytesAsString(byteBuffer, 8, 4)
        << endl << endl;
}

void Reader::readFmtSubChunk(const vector<uint8_t>& byteBuffer) {
    cout << "============== fmt sub-chunk ==============" << endl;
    cout << "fmt sub-chunk SubChunk1ID: " << readBytesAsString(
            byteBuffer,
            12,
            3
        )
        << endl;

    cout << "fmt sub-chunk SubChunk1Size: " << read4BytesAsInt(byteBuffer, 16)
        << endl;

    cout << "fmt sub-chunk AudioFormat: " << read2BytesAsInt(byteBuffer, 20)
        << endl;

    cout << "fmt sub-chunk NumChannels: " << read2BytesAsInt(byteBuffer, 22)
        << endl;

    cout << "fmt sub-chunk SampleRate: " << read4BytesAsInt(byteBuffer, 24)
        << " Hz"
        << endl;

    const int bytesPerSecond = read4BytesAsInt(byteBuffer, 28);
    cout << "fmt sub-chunk ByteRate: " << bytesPerSecond << " bytes/second ("
        << static_cast<float>(bytesPerSecond) * 8.0f / 1000.0f
        << " Kilobits/second)"
        << endl;

    cout << "fmt sub-chunk BlockAlign: " << read2BytesAsInt(byteBuffer, 32)
        << endl;

    cout << "fmt sub-chunk BitsPerSample: " << read2BytesAsInt(byteBuffer, 34)
        << endl << endl;
}

void Reader::readTotalFileSize(const vector<uint8_t>& byteBuffer) {
    cout << "Total file size: " << byteBuffer.size()
        << " Bytes ("
        << floorf((static_cast<float>(byteBuffer.size()) / 1'000'000.0f) * 100) / 100
        << " MB)"
        << endl << endl;
}

void Reader::readDataSubChunk(const vector<uint8_t>& byteBuffer) {
    cout << "============= data sub-chunk ==============" << endl;
    cout << "data sub-chunk SubChunk2ID: " << readBytesAsString(
            byteBuffer,
            36,
            4
        )
        << endl;

    cout << "data sub-chunk SubChunk2Size: " << read4BytesAsInt(byteBuffer, 40)
        << endl;
}
