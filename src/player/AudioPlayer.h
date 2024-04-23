#pragma once

#include <rtaudio/RtAudio.h>
#include "../FileReader.hpp"

class AudioPlayer {
public:
    explicit AudioPlayer(const DataView& dataView);
    void play() const;

private:
    const DataView& dataView;
    const unique_ptr<RtAudio> rtAudio;
};
