#include <iostream>
#include <ranges>
#include "include/cli11/CLI11.hpp"
#include "FileReader.h"

using std::string, std::endl, std::cout, std::vector;

void printSplashText() {
    cout << endl << ".wav file format specification taken from:" << endl
        << "https://ccrma.stanford.edu/courses/422-winter-2014/projects/WaveFormat/"
        << endl
        << "Created by Danny Priymak"
        << endl
        << "https://github.com/daisp/wav_decoder"
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


int main(const int argc, char* argv[]) {
    printSplashText();
    CLI::App app{".wav file decoder"};
    argv = app.ensure_utf8(argv);

    string inputFilePath;
    app.add_option("-i,--inputFilePath", inputFilePath,
                   "The path of the .wav file to decode.");
    CLI11_PARSE(app, argc, argv);

    const auto reader = FileReader(inputFilePath);
    reader.read();

    return 0;
}
