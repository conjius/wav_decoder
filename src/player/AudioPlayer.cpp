#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(const DataView& dataView) :
    dataView(dataView),
    rtAudio(make_unique<RtAudio>()) {
}

void AudioPlayer::play() const {
    const uint8_t devices = this->rtAudio->getDeviceCount();
    for (int i = 1; i <= devices; i++) {
        const RtAudio::DeviceInfo info = this->rtAudio->getDeviceInfo(i);

        // Log, for example, the maximum number of output channels for each device
        spdlog::info("device = {}", i);
        spdlog::info(": maximum output channels = {}", info.outputChannels);
    }
}
