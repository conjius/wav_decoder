#include "FxProcessor.hpp"
#include "../FileReaderReadResult.hpp"
#include "../cli/CliArgParser.hpp"

using std::unique_ptr;

FxProcessor::FxProcessor(
    const FileReaderReadResult& fileReaderReadResult,
    const vector<shared_ptr<Effect>>& effects):
    fileReaderReadResult(fileReaderReadResult), effects(effects) {
}

void FxProcessor::apply() const {
    for (const shared_ptr<Effect>& effect : this->effects) {
        effect->apply(this->fileReaderReadResult.data);
    }
}
