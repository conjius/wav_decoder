#include <iostream>
#include "FileReader.hpp"
#include "cli/CliArgParser.hpp"
#include "fx/FxProcessor.hpp"
#include "player/AudioPlayer.h"

using std::string, std::endl, std::vector;

void printSplashText() {
    spdlog::info("\n.wav file format specification taken from:");
    spdlog::info(
        "https://ccrma.stanford.edu/courses/422-winter-2014/projects/WaveFormat/\n"
    );
    spdlog::info("Created by Danny Priymak");
    spdlog::info("https://github.com/daisp/wav_decoder");
    spdlog::info(R"(                               _                    _           )");
    spdlog::info(R"( __      ____ ___   __      __| | ___  ___ ___   __| | ___ _ __ )");
    spdlog::info(R"( \ \ /\ / / _` \ \ / /____ / _` |/ _ \/ __/ _ \ / _` |/ _ \ '__|)");
    spdlog::info(R"(  \ V  V / (_| |\ V /_____| (_| |  __/ (_| (_) | (_| |  __/ |   )");
    spdlog::info(
        R"(   \_/\_/ \__,_| \_/       \__,_|\___|\___\___/ \__,_|\___|_|   )""\n");
}


int main(const int argc, char* argv[]) {
    const auto cliArgParser = CliArgParser(argc, argv);
    const auto [
        inputFilePathString,
        logLevelString,
        isQuiet,
        effects
    ] = cliArgParser.parse();

    spdlog::set_level(isQuiet ? spdlog::level::err : spdlog::level::info);
    printSplashText();

    auto reader = FileReader(inputFilePathString);
    const auto fileReaderReadResult = reader.read();

    const auto fxProcessor = FxProcessor(fileReaderReadResult, effects);
    fxProcessor.apply();

    const auto player = AudioPlayer(fileReaderReadResult.data);
    player.play();
    return 0;
}
