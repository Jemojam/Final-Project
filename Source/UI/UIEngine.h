#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "ToolbarComponent.h"
#include "ChannelWindow.h"
#include "AudioSettings.h"

class UIEngine : public Component
{
public:
	UIEngine(AudioEngine& inEngine);
	~UIEngine();

	void paint(Graphics& g) override;
	void resized() override;

private:
	ToolbarComponent toolbar;
	ChannelWindow channelWindow;

    
	AudioEngine& engine;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIEngine)
};
