
#include "ChannelComponent.h"


ChannelComponent::ChannelComponent(AudioEngine& inEngine, AudioTrack& inTrack) : engine(inEngine), track(inTrack)
{

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

    slider.reset(new Slider("new slider"));
    addAndMakeVisible(slider.get());
    slider->setRange(-30, 6, 0);
    slider->setSliderStyle(Slider::LinearHorizontal);
    slider->setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    slider->setColour(Slider::thumbColourId, Colour(0xffbebebe));
    slider->addListener(this);

    slider->setBounds(120, 40, 79, 24);

    muteButton.reset(new ImageButton("muteBotton"));
    addAndMakeVisible(muteButton.get());
    muteButton->setButtonText(TRANS("Mute"));
    muteButton->addListener(this);

    muteButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_033mute_png, BinaryData::_033mute_pngSize), 1.000f, Colours::white,
                          Image(), 1.000f, Colour(0x00000000),
                          Image(), 1.000f, Colour(0x00000000));
    muteButton->setBounds(32, 40, 15, 15);

    soloButton.reset(new ImageButton("soloButton"));
    addAndMakeVisible(soloButton.get());
    soloButton->setButtonText(TRANS("Solo"));
    soloButton->addListener(this);

    soloButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_048headphones_png, BinaryData::_048headphones_pngSize), 1.000f, Colours::white,
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
                        ImageCache::getFromMemory(BinaryData::_072settings_png, BinaryData::_072settings_pngSize), 1.000f, Colours::white,
                        Image(), 1.000f, Colour(0x00000000),
                        Image(), 1.000f, Colour(0x00000000));
    FXButton->setBounds(160, 8, 15, 15);

}


ChannelComponent::~ChannelComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    selectButton = nullptr;
    nameText = nullptr;
    slider = nullptr;
    muteButton = nullptr;
    soloButton = nullptr;
    addFileButton = nullptr;
    FXButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ChannelComponent::paint(Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(Colour(0xff323e44));

    {
        float x = 0.0f, y = 0.0f, width = 200.0f, height = 70.0f;
        Colour fillColour1 = Colour(0xff4a4a4a), fillColour2 = Colour(0xff262626);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
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
    if (audioThumbnailComponent != nullptr)
        audioThumbnailComponent->setBounds(204, 0, getLocalBounds().getWidth(), getLocalBounds().getHeight());
}
/*
void ChannelComponent::valueTreePropertyChanged(juce::ValueTree& v, const juce::Identifier& i)
{
	if (te::TrackList::isTrack(v))
	{
		if (i == te::IDs::mute)
			muteButton->setToggleState((bool)v[i], dontSendNotification);
		else if (i == te::IDs::solo)
			soloButton->setToggleState((bool)v[i], dontSendNotification);
	}
	else if (v.hasType(te::IDs::INPUTDEVICES) || v.hasType(te::IDs::INPUTDEVICE))
	{
		if (auto at = dynamic_cast<te::AudioTrack*> (&track))
		{
			selectButton->setEnabled(engine.trackHasInput(*at));
			selectButton->setToggleState(engine.isTrackArmed(*at), dontSendNotification);
		}
	}
}
*/

void ChannelComponent::buttonClicked(Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == selectButton.get())
    {
        engine.armTrack(track, !engine.isTrackArmed(track));
        selectButton->setToggleState(engine.isTrackArmed(track), dontSendNotification);

        if (selectButton->getToggleState())
        {
            selectButton->setColour(selectButton->buttonColourId, Colours::orange);
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon, "!", "!");
        }
        else
        {
            selectButton->setColour(selectButton->buttonColourId, Colour(0xff1b605e));
        }

    }
    else if (buttonThatWasClicked == muteButton.get())
    {
        engine.muteChannel(track);
    }
    else if (buttonThatWasClicked == soloButton.get())
    {
        engine.soloChannel(track);
    }
    else if (buttonThatWasClicked == addFileButton.get())
    {
        auto location = File::getSpecialLocation(File::userDesktopDirectory);

        FileChooser chooser("Choose a file", location, "*.wav", true, false);

        if (chooser.browseForFileToOpen())
        {
            auto file = chooser.getResult();

            engine.addNewClipFromFile(file, track);

            audioThumbnailComponent.reset(new AudioThumbnailComponent(engine));
            audioThumbnailComponent->setSourceThumbnail(file);
            addAndMakeVisible(*audioThumbnailComponent);
            resized();
        }

    }
    else if (buttonThatWasClicked == FXButton.get())
    {
        engine.inputMonitoring(&track);
    }

}

void ChannelComponent::sliderValueChanged(Slider* sliderThatWasMoved)
{

    if (sliderThatWasMoved == slider.get())
    {
        auto volume = (float) sliderThatWasMoved->getValue();
        engine.changeVolume(track, volume);

    }

}




