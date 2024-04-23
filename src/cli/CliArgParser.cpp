#include "CliArgParser.hpp"

#include "../StringUtils.hpp"
#include "../fx/EffectBuilder.hpp"

CliArgParser::CliArgParser(const int& argcount, char** argvector) : argc(argcount),
    argv(argvector) {
    this->app = make_unique<CLI::App>(".wav file decoder");
    this->argv = this->app->ensure_utf8(this->argv);
}

CliArgParserParseResult CliArgParser::parse() const {
    string inputFilePathString;
    this->app->add_option(
        "-i,--inputFilePath", inputFilePathString,
        "The path of the .wav file to decode."
    )->required();

    string logLevelString = "info";
    this->app->add_option(
        "--loglevel", logLevelString,
        "The log verbosity level. Supported values are "
        "[debug, info, warn, error, critical]"
    )->capture_default_str();

    bool isQuiet = false;
    this->app->add_flag(
        "-q,--quiet", isQuiet,
        "Run in quiet mode. Equivalent to running the program with "
        "the --loglevel error flag."
    )->capture_default_str();

    string fxInput;
    this->app->add_option(
            "--fx", fxInput,
            "Apply audio effects to the input file. Supported effects include:\n"
            "  volume=[0.0-1.0]: Set the volume, where 0.0 is mute and 1.0 is maximum volume.\n")
        ->capture_default_str();

    try {
        this->app->parse(this->argc, this->argv);
    }

    catch (const CLI::ParseError& e) {
        throw std::runtime_error(
            string("Error while parsing CLI arguments: ") + e.what()
        );
    }

    const auto effects = parseFxInput(fxInput);

    return CliArgParserParseResult{
        inputFilePathString,
        logLevelString,
        isQuiet,
        effects
    };
}

vector<shared_ptr<Effect>> CliArgParser::parseFxInput(const string& fxInput) {
    vector<shared_ptr<Effect>> effects;
    for (const string& effectPairString : StringUtils::split(fxInput, ',')) {
        auto effectStringPair = StringUtils::split(effectPairString, '=');
        auto effect = EffectBuilder::from(
            effectStringPair.at(0),
            effectStringPair.at(1)
        );
        effects.push_back(effect);
    }
    return effects;
}
