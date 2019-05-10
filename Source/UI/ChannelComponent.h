#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "AudioThumbnailComponent.h"


class ChannelComponent : public Component, 
						 public Button::Listener,
						 public Slider::Listener, 
						 private te::ValueTreeAllEventListener

{
public:
	
	ChannelComponent(AudioEngine& inEngine, AudioTrack& inTrack);
	~ChannelComponent();

	void paint(Graphics& g) override;
	void resized() override;
	
	
	void buttonClicked(Button* buttonThatWasClicked) override;
	void sliderValueChanged(Slider* sliderThatWasMoved) override;
	bool isSelected() { return selected; };


private:
	void valueTreeChanged() override {};
	//void valueTreePropertyChanged(juce::ValueTree& v, const juce::Identifier& i) override;

	std::unique_ptr<TextButton> selectButton;
	std::unique_ptr<TextEditor> nameText;
	std::unique_ptr<Slider> slider;
	std::unique_ptr<ImageButton> muteButton;
	std::unique_ptr<ImageButton> soloButton;
	std::unique_ptr<ImageButton> addFileButton;
	std::unique_ptr<ImageButton> FXButton;

	std::unique_ptr<AudioThumbnailComponent> audioThumbnailComponent;

	ValueTree inputsState;
	AudioEngine& engine;
	AudioTrack& track;

	bool selected = false;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChannelComponent)
};