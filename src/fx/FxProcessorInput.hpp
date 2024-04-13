#pragma once

#include "../FileReaderReadResult.hpp"

using std::string;

class FxProcessorInput {
public:
    static FxProcessorInput fromFileReaderReadResult(
        const FileReaderReadResult& readResult
    ) {
        return FxProcessorInput{
            readResult
        };
    }

    vector<string>& fxNames;
};
