#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "Audio/Metronome.h"
#include "PlayButton.h"



class ToolbarComponent  : public Component,
                          public Button::Listener
{
public:
    //==============================================================================
    ToolbarComponent (AudioEngine& inEngine);
    ~ToolbarComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

	void getCurrentTimeText();

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ImageButton> recordButton;
    std::unique_ptr<ImageButton> stopButton;
    std::unique_ptr<ImageButton> loopButton;
    std::unique_ptr<TextEditor> timeText;
    std::unique_ptr<TextEditor> bpmText;
    std::unique_ptr<TextEditor> barsText;
    std::unique_ptr<ImageButton> metronomeButton;
	std::unique_ptr<ImageButton> audioSettingsButton;
	std::unique_ptr<ImageButton> exportFileButton;
	

	
    PlayButton playButton;

    AudioEngine& engine;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToolbarComponent)
};

