#pragma once

#include "JuceHeader.h"
#include "ChannelComponent.h"
#include "Audio/AudioEngine.h"

class ChannelWindow : public Component, public Timer
{
public:
    ChannelWindow(AudioEngine& inEngine);

    void paint(Graphics& g) override;
    void timerCallback() override;

private:

    AudioEngine& engine;

    std::vector<std::unique_ptr<ChannelComponent>> channels;
    void rebuildTrackList();
};