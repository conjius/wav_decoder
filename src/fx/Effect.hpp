#pragma once
#include "../FileReader.hpp"

using std::variant;

using EffectValue = variant<int, float, bool, string>;

class Effect {
public:
    Effect() = delete;
    virtual ~Effect() = default;

    explicit Effect(EffectValue value) : value(std::move(value)) {
    };

    virtual void apply(const DataView& dataView) = 0;

protected:
    const EffectValue value;
};

class VolumeEffect final : public Effect {
public:
    explicit VolumeEffect(const EffectValue& value)
        : Effect(value) {
    }

    void apply(const DataView& dataView) override {
        for (unsigned char& sample : dataView) {
            sample *= std::get<float>(this->value);
        }
    }
};
