#pragma once

class Converter {
public:
    static float byteRateToKiloBitRate(const int& ByteRate) {
        return static_cast<float>(ByteRate) * 8.0f / 1000.0f;
    }
};
