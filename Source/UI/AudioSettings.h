

#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "C:/CODE/JUCE/examples/Assets/DemoUtilities.h"

class AudioSettings  : public Component,
                       public ChangeListener
{
public:
    AudioSettings();
    ~AudioSettings();

    void paint (Graphics& g) override;
    void resized() override;

    void dumpDeviceInfo();
    void logMessage (const String& m);

private:
  

    std::unique_ptr<AudioDeviceSelectorComponent> audioSetupComp;
    TextEditor diagnosticsBox;
	AudioDeviceManager audioDeviceManager;

    void changeListenerCallback (ChangeBroadcaster*) override;
    void lookAndFeelChanged() override;
    String getListOfActiveBits (const BigInteger& b);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSettings)
};
