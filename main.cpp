#include <iostream>
#include <ranges>
#include "cli11/CLI11.hpp"

using std::string, std::endl, std::cout;

void printSplashText() {
    cout << endl << ".wav file format specification taken from:" << endl
        << "https://ccrma.stanford.edu/courses/422-winter-2014/projects/WaveFormat/"
        << endl
        << R"(                               _                    _           )"
        << endl
        << R"( __      ____ ___   __      __| | ___  ___ ___   __| | ___ _ __ )"
        << endl
        << R"( \ \ /\ / / _` \ \ / /____ / _` |/ _ \/ __/ _ \ / _` |/ _ \ '__|)"
        << endl
        << R"(  \ V  V / (_| |\ V /_____| (_| |  __/ (_| (_) | (_| |  __/ |   )"
        << endl
        << R"(   \_/\_/ \__,_| \_/       \__,_|\___|\___\___/ \__,_|\___|_|   )"
        << endl << endl;
}

void readRIFFChunkDescriptor(const std::vector<unsigned char>& buffer) {
    cout << "========== RIFF chunk descriptor ==========" << endl;
    const auto riffChunkIdByteRange = buffer | std::ranges::views::drop(0)
        | std::ranges::views::take(4);
    cout << "ChunkID: ";
    for (const auto c : riffChunkIdByteRange) {
        std::cout << c;
    }
    cout << endl;

    cout << "ChunkSize: " << static_cast<int>(buffer.at(5)) << endl;

    cout << "Format: ";
    const auto riffChunkFormatByteRange =
        buffer | std::ranges::views::drop(8) | std::ranges::views::take(4);
    for (const auto c : riffChunkFormatByteRange) {
        std::cout << c;
    }
    cout << endl << endl;
}

void readFmtSubChunk(const std::vector<unsigned char>& buffer) {
    cout << "============== fmt sub-chunk ==============" << endl;
    const auto riffChunkIdByteRange = buffer | std::ranges::views::drop(12)
        | std::ranges::views::take(3);
    cout << "fmt SubChunk1ID: ";
    for (const auto c : riffChunkIdByteRange) {
        std::cout << c;
    }
    cout << endl;
}

void readTotalFileSize(const std::vector<unsigned char> buffer) {
    cout << "Total file size in bytes: " << buffer.size() << " ("
        << floorf((static_cast<float>(buffer.size()) / 1'000'000.0f) * 100) / 100 << " MB)"
        << endl << endl;
}

int main(const int argc, char* argv[]) {
    printSplashText();
    CLI::App app{".wav file decoder"};
    argv = app.ensure_utf8(argv);
    string inputFilePath;
    app.add_option("-i,--input", inputFilePath,
                   "The path of the .wav file to decode.");
    CLI11_PARSE(app, argc, argv);

    std::ifstream input(inputFilePath, std::ios::binary);
    const std::vector<unsigned char> buffer(std::istreambuf_iterator(input), {});

    readTotalFileSize(buffer);
    readRIFFChunkDescriptor(buffer);
    readFmtSubChunk(buffer);

    return 0;
}
