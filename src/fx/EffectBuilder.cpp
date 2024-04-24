#include "EffectBuilder.hpp"

#include <CLI/CLI.hpp>

shared_ptr<Effect> EffectBuilder::from(const string& name, const string& valueString) {
    if (name == "volume") {
        const auto value = parseStringToArgValue(valueString);
        auto volumeEffectPtr = std::make_shared<VolumeEffect>(VolumeEffect(value));
        return volumeEffectPtr;
    }
    throw CLI::ValidationError(
        "Unsupported effect provided: {}. Supported effects are [volume]", name
    );
}

void EffectBuilder::resetInputStringStream(std::istringstream& iss, const string& str) {
    iss.clear();
    iss.str(str);
}

EffectValue EffectBuilder::parseStringToArgValue(const string& str) {
    std::istringstream iss(str);

    int i;
    if (iss >> i && iss.eof()) {
        return i;
    }
    resetInputStringStream(iss, str);

    float f;
    if (iss >> f && iss.eof()) {
        return f;
    }
    resetInputStringStream(iss, str);

    bool b;
    if (iss >> std::boolalpha >> b && iss.eof()) {
        return b;
    }

    return str;
}
