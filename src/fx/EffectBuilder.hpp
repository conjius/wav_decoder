#pragma once
#include "Effect.hpp"

using std::shared_ptr;

class EffectBuilder {
public:
    static shared_ptr<Effect> from(const string& name, const string& valueString);

private:
    static void resetInputStringStream(std::istringstream& iss, const string& str);

    static EffectValue parseStringToArgValue(const string& str);
};
