#include "JuceHeader.h"
#include "AudioEngine.h"
#include "ToolbarComponent.h"
#include "ChannelComponent.h"
#pragma once
class UIEngine : public Component
{
public:

	UIEngine();
	~UIEngine();

	void paint(Graphics& g) override;
	void resized() override;
	void addNewChannel();
	
	

private:
	ToolbarComponent toolbar;
	//std::vector<std::unique_ptr<ChannelComponent>> channels;
	//Array <std::unique_ptr<ChannelComponent>> channels;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIEngine)
};
