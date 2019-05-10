
#include "ChannelComponent.h"

const Colour notArmedColor = Colour(0xff1b605e);

ChannelComponent::ChannelComponent(AudioEngine& inEngine, AudioTrack& inTrack)
        : engine(inEngine),
          track(inTrack)
{
    shouldUpdate.reset(new std::atomic<bool>(false));
    startTimerHz(60);

    track.state.addListener(this);

    selectButton.reset(new TextButton("selectButton"));
    addAndMakeVisible(selectButton.get());
    selectButton->setButtonText(String());
    selectButton->addListener(this);
    selectButton->setColour(TextButton::buttonColourId, Colour(0xff1b605e));

    selectButton->setBounds(8, 8, 18, 52);

    nameText.reset(new TextEditor("nameText"));
    addAndMakeVisible(nameText.get());
    nameText->setMultiLine(false);
    nameText->setReturnKeyStartsNewLine(false);
    nameText->setReadOnly(false);
    nameText->setScrollbarsShown(true);
    nameText->setCaretVisible(true);
    nameText->setPopupMenuEnabled(true);
    nameText->setText(String());

    nameText->setBounds(40, 8, 88, 16);

    volumeSlider.reset(new Slider("new slider"));
    addAndMakeVisible(volumeSlider.get());
    volumeSlider->setRange(-30, 6, 0);
    volumeSlider->setSliderStyle(Slider::LinearHorizontal);
    volumeSlider->setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    volumeSlider->setColour(Slider::thumbColourId, Colour(0xffbebebe));
    volumeSlider->addListener(this);

    volumeSlider->setBounds(120, 40, 79, 24);

    muteButton.reset(new ImageButton("muteBotton"));
    addAndMakeVisible(muteButton.get());
    muteButton->setButtonText(TRANS("Mute"));
    muteButton->addListener(this);

    muteButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_033mute_png, BinaryData::_033mute_pngSize), 1.000f,
                          Colours::white,
                          Image(), 1.000f, Colour(0x00000000),
                          Image(), 1.000f, Colour(0x00000000));
    muteButton->setBounds(32, 40, 15, 15);

    soloButton.reset(new ImageButton("soloButton"));
    addAndMakeVisible(soloButton.get());
    soloButton->setButtonText(TRANS("Solo"));
    soloButton->addListener(this);

    soloButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_048headphones_png, BinaryData::_048headphones_pngSize),
                          1.000f, Colours::white,
                          Image(), 1.000f, Colour(0x00000000),
                          Image(), 1.000f, Colour(0x00000000));
    soloButton->setBounds(64, 40, 15, 15);

    addFileButton.reset(new ImageButton("addFileButton"));
    addAndMakeVisible(addFileButton.get());
    addFileButton->setButtonText(TRANS("Add File"));
    addFileButton->addListener(this);

    addFileButton->setImages(false,
                             true,
                             true,
                             ImageCache::getFromMemory(BinaryData::_074folder_png, BinaryData::_074folder_pngSize),
                             1.000f,
                             Colours::white,
                             Image(),
                             1.000f,
                             Colours::white,
                             Image(),
                             1.000f,
                             Colours::lightgreen);
    addFileButton->setBounds(96, 40, 15, 15);

    FXButton.reset(new ImageButton("FXButton"));
    addAndMakeVisible(FXButton.get());
    FXButton->setButtonText(TRANS("FX"));
    FXButton->addListener(this);

    FXButton->setImages(false, true, true,
                        ImageCache::getFromMemory(BinaryData::_072settings_png, BinaryData::_072settings_pngSize),
                        1.000f, Colours::white,
                        Image(), 1.000f, Colour(0x00000000),
                        Image(), 1.000f, Colour(0x00000000));
    FXButton->setBounds(160, 8, 15, 15);

}

void ChannelComponent::paint(Graphics& g)
{
    g.fillAll(Colour(0xff323e44));

    {
        float x = 0.0f, y = 0.0f, width = 200.0f, height = 70.0f;
        Colour fillColour1 = Colour(0xff4a4a4a), fillColour2 = Colour(0xff262626);

        g.setGradientFill(ColourGradient(Colours::black,
                                         176.0f - 0.0f + x,
                                         16.0f - 0.0f + y,
                                         fillColour2,
                                         104.0f - 0.0f + x,
                                         48.0f - 0.0f + y,
                                         false));

        g.fillRoundedRectangle(x, y, width, height, 10.000f);
    }

}

void ChannelComponent::resized()
{
    auto bounds = getLocalBounds();

    for (auto& thumbnail: audioThumbnailComponents)
    {
        thumbnail->setBounds(204, 0, bounds.getWidth(), bounds.getHeight());
    }
}

void ChannelComponent::buttonClicked(Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == selectButton.get())
        clickSelectButton();

    else if (buttonThatWasClicked == muteButton.get())
        engine.muteChannel(track);

    else if (buttonThatWasClicked == soloButton.get())
        engine.soloChannel(track);

    else if (buttonThatWasClicked == addFileButton.get())
        clickAddFileButton();

    else if (buttonThatWasClicked == FXButton.get())
        engine.inputMonitoring(&track);

}

void ChannelComponent::clickAddFileButton()
{
    auto location = File::getSpecialLocation(File::userDesktopDirectory);

    FileChooser chooser("Choose a file", location, "*.wav", true, false);

    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();

        engine.addNewClipFromFile(file, track);
    }
}

void ChannelComponent::clickSelectButton() const
{
    bool shouldArm = !engine.isTrackArmed(track);

    engine.armTrack(track, shouldArm);

    selectButton->setToggleState(engine.isTrackArmed(track), dontSendNotification);
    selectButton->setColour(selectButton->buttonColourId, getArmedTrackColor());
}

Colour ChannelComponent::getArmedTrackColor() const
{
    auto color = notArmedColor;

    if (selectButton->getToggleState())
        color = Colours::orange;

    return color;
}

void ChannelComponent::sliderValueChanged(Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == volumeSlider.get())
    {
        auto volume = (float) sliderThatWasMoved->getValue();
        engine.changeVolume(track, volume);
    }
}

void ChannelComponent::timerCallback()
{
    if (shouldUpdate->load())
    {
        shouldUpdate->store(false);
        rebuildClips();
    }
}

void ChannelComponent::rebuildClips()
{
    audioThumbnailComponents.clear();

    for (auto* clip:track.getClips())
    {
        audioThumbnailComponents.emplace_back();

        auto& newThumnail = audioThumbnailComponents.back();
        newThumnail.reset(new AudioThumbnailComponent(*clip));

        addAndMakeVisible(*newThumnail);
    }

    resized();
}



