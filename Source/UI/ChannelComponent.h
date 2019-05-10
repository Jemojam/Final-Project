#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
#include "AudioThumbnailComponent.h"

class ChannelComponent : public Component,
                         public Button::Listener,
                         public Slider::Listener,
                         private te::ValueTreeAllEventListener,
                         public Timer
{
public:

    ChannelComponent(AudioEngine& inEngine, AudioTrack& inTrack);

    void paint(Graphics& g) override;
    void resized() override;


    void buttonClicked(Button* buttonThatWasClicked) override;
    void sliderValueChanged(Slider* sliderThatWasMoved) override;
    bool isSelected() { return selected; };
    void timerCallback() override;

private:
    void clickSelectButton() const;
    void clickAddFileButton();
    void valueTreeChanged() override {};
    Colour getArmedTrackColor() const;

    std::unique_ptr<TextButton> selectButton;
    std::unique_ptr<TextEditor> nameText;
    std::unique_ptr<Slider> volumeSlider;
    std::unique_ptr<ImageButton> muteButton;
    std::unique_ptr<ImageButton> soloButton;
    std::unique_ptr<ImageButton> addFileButton;
    std::unique_ptr<ImageButton> FXButton;

    std::vector <std::unique_ptr<AudioThumbnailComponent>> audioThumbnailComponents;

    ValueTree inputsState;
    AudioEngine& engine;
    AudioTrack& track;

    std::unique_ptr<std::atomic<bool>> shouldUpdate;

    bool selected = false;
    void rebuildClips();
};