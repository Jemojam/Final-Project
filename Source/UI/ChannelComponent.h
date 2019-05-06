#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "AudioThumbnailComponent.h"


class ChannelComponent : public Component, 
						 public Button::Listener,
						 public Slider::Listener 

{
public:
	
	ChannelComponent(AudioEngine& inEngine, AudioTrack& inTrack);
	~ChannelComponent();

	void paint(Graphics& g) override;
	void resized() override;
	//void valueTreePropertyChanged(juce::ValueTree& v, const juce::Identifier& i) override;
	
	void buttonClicked(Button* buttonThatWasClicked) override;
	void sliderValueChanged(Slider* sliderThatWasMoved) override;
	bool isSelected() { return selected; };

	// Binary resources:
	static const char* musicwoofersquarebox_png;
	static const int musicwoofersquarebox_pngSize;
	static const char* musicsound_png;
	static const int musicsound_pngSize;
	static const char* mutevolumecontrol_png;
	static const int mutevolumecontrol_pngSize;
	static const char* musicfoldervariant_png;
	static const int musicfoldervariant_pngSize;
	static const char* soundbarsformedbysmallcircles_png;
	static const int soundbarsformedbysmallcircles_pngSize;
	static const char* headphonesymbol_png;
	static const int headphonesymbol_pngSize;
	static const char* _033mute_png;
	static const int _033mute_pngSize;
	static const char* _048headphones_png;
	static const int _048headphones_pngSize;
	static const char* _072settings_png;
	static const int _072settings_pngSize;
	static const char* _023record_png;
	static const int _023record_pngSize;


private:

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