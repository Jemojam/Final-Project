#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioEngine.h"
#pragma once

class ToolbarComponent  : public Component,
                          public Button::Listener
						  
{
public:

    ToolbarComponent ();
    ~ToolbarComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

    // Binary resources:
    static const char* play_png;
    static const int play_pngSize;
    static const char* stop_png;
    static const int stop_pngSize;
    static const char* record_png;
    static const int record_pngSize;
    static const char* loop_png;
    static const int loop_pngSize;
    static const char* rec_png;
    static const int rec_pngSize;
    static const char* playbuttonarrowhead_png;
    static const int playbuttonarrowhead_pngSize;
    static const char* musicpausebuttonpairoflines_png;
    static const int musicpausebuttonpairoflines_pngSize;
    static const char* circleinblackofadrumtopview_png;
    static const int circleinblackofadrumtopview_pngSize;
    static const char* starshapedbrush_png;
    static const int starshapedbrush_pngSize;

private:

    std::unique_ptr<ImageButton> recordButton;
    std::unique_ptr<ImageButton> stopButton;
    std::unique_ptr<ImageButton> playButton;
    std::unique_ptr<ImageButton> loopButton;
    std::unique_ptr<TextEditor> timeText;
    std::unique_ptr<TextEditor> bpmText;
    std::unique_ptr<TextEditor> barsText;
    std::unique_ptr<ImageButton> addChannelButton;

	AudioEngine * audioEngine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToolbarComponent)
};

