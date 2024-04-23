#pragma once
#include <string>
#include <CLI/CLI.hpp>
#include "../fx/Effect.hpp"

using std::string, std::unique_ptr, std::make_unique, std::vector, std::map,
    std::variant, std::shared_ptr;

struct CliArgParserParseResult {
    const string inputFilePathString;
    const string logLevelString;
    const bool isQuiet;
    const vector<shared_ptr<Effect>> effects;
};

class CliArgParser {
public:
    CliArgParser(const int& argcount, char** argvector);
    [[nodiscard]] CliArgParserParseResult parse() const;

private:
    [[nodiscard]] static vector<shared_ptr<Effect>> parseFxInput(
        const string& fxInput
    );
    unique_ptr<CLI::App> app;
    const int& argc;
    char** argv;
};
