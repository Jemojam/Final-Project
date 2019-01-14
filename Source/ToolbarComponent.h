/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ToolbarComponent  : public Component,
                          public Button::Listener
{
public:
    //==============================================================================
    ToolbarComponent ();
    ~ToolbarComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

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
    static const char* _028play_png;
    static const int _028play_pngSize;
    static const char* _013stop_png;
    static const int _013stop_pngSize;
    static const char* _023record_png;
    static const int _023record_pngSize;
    static const char* _075audiofile_png;
    static const int _075audiofile_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ImageButton> recordButton;
    std::unique_ptr<ImageButton> stopButton;
    std::unique_ptr<ImageButton> playButton;
    std::unique_ptr<ImageButton> loopButton;
    std::unique_ptr<TextEditor> timeText;
    std::unique_ptr<TextEditor> bpmText;
    std::unique_ptr<TextEditor> barsText;
    std::unique_ptr<ImageButton> addChannelButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToolbarComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
