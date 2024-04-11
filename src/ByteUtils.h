#pragma once

using std::vector, std::string;

inline int read4BytesAsInt(const vector<uint8_t>& byteBuffer, const int bufferOffset) {
    return (
        byteBuffer.at(bufferOffset)
        | (byteBuffer.at(bufferOffset + 1) << 8)
        | (byteBuffer.at(bufferOffset + 2) << 16)
        | (byteBuffer.at(bufferOffset + 3) << 32)
    );
}

inline int read2BytesAsInt(const vector<uint8_t>& byteBuffer, const int bufferOffset) {
    return (
        byteBuffer.at(bufferOffset)
        | (byteBuffer.at(bufferOffset + 1) << 8)
    );
}

inline string readBytesAsString(const vector<uint8_t>& byteBuffer,
                              const int bufferOffset,
                              const int numBytesToRead) {
    string result;
    const auto byteBufferRange =
        byteBuffer
        | std::ranges::views::drop(bufferOffset)
        | std::ranges::views::take(numBytesToRead);

    for (const auto c : byteBufferRange) {
        result += c;
    }

    return result;
}
