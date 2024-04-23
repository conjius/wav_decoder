#pragma once

#include <map>

#include "Effect.hpp"
#include "../FileReaderReadResult.hpp"
#include "../cli/CliArgParser.hpp"

using std::map;

class FxProcessor {
public:
    FxProcessor(const FileReaderReadResult& fileReaderReadResult,
                const vector<shared_ptr<Effect>>& effectPairs);
    void apply() const;

private:
    const FileReaderReadResult& fileReaderReadResult;
    const vector<shared_ptr<Effect>>& effects;
};
