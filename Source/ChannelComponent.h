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
class ChannelComponent  : public Component,
                          public Button::Listener,
                          public Slider::Listener
{
public:
    //==============================================================================
    ChannelComponent ();
    ~ChannelComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

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
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> selectButton;
    std::unique_ptr<TextEditor> nameText;
    std::unique_ptr<Slider> slider;
    std::unique_ptr<ImageButton> muteBotton;
    std::unique_ptr<ImageButton> soloButton;
    std::unique_ptr<ImageButton> addFileButton;
    std::unique_ptr<ImageButton> FXButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
