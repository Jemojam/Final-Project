#include "ToolbarComponent.h"


//==============================================================================
ToolbarComponent::ToolbarComponent(AudioEngine& inEngine) :
        playButton(inEngine),
        engine(inEngine)
{
    recordButton.reset(new ImageButton("recordButton"));
    addAndMakeVisible(recordButton.get());
    recordButton->setButtonText(TRANS("new button"));
    recordButton->addListener(this);

    recordButton->setImages(false, true, true,
                            ImageCache::getFromMemory(BinaryData::_023record_png, BinaryData::_023record_pngSize), 1.0f,
                            Colours::crimson,
                            Image(), 1.0f, Colour(0x00000000),
                            Image(), 1.0f, Colour(0x00000000));
    recordButton->setBounds(384, 39, 16, 19);

    stopButton.reset(new ImageButton("stopButton"));
    addAndMakeVisible(stopButton.get());
    stopButton->setButtonText(TRANS("new button"));
    stopButton->addListener(this);

    stopButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_013stop_png, BinaryData::_013stop_pngSize), 1.0f,
                          Colours::darkturquoise,
                          Image(), 1.0f, Colour(0x00000000),
                          Image(), 1.0f, Colour(0x00000000));
    stopButton->setBounds(352, 40, 16, 16);

    addAndMakeVisible(playButton);

    playButton.setBounds(320, 40, 16, 16);

    loopButton.reset(new ImageButton("loopButton"));
    addAndMakeVisible(loopButton.get());
    loopButton->setButtonText(String());
    loopButton->addListener(this);

    loopButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::_081loop_png, BinaryData::_081loop_pngSize), 1.0f,
                          Colours::orangered,
                          Image(), 1.0f, Colour(0x00000000),
                          Image(), 1.0f, Colour(0x00000000));
    loopButton->setBounds(414, 35, 16, 27);

    timeText.reset(new TextEditor("timeText"));
    addAndMakeVisible(timeText.get());
    timeText->setMultiLine(false);
    timeText->setReturnKeyStartsNewLine(false);
    timeText->setReadOnly(false);
    timeText->setScrollbarsShown(true);
    timeText->setCaretVisible(true);
    timeText->setPopupMenuEnabled(true);
    timeText->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    timeText->setColour(TextEditor::highlightColourId, Colour(0xb21a574e));
    timeText->setText(TRANS("00 : 00 : 00"));

    timeText->setBounds(64, 46, 80, 16);

    bpmText.reset(new TextEditor("bpmText"));
    addAndMakeVisible(bpmText.get());
    bpmText->setMultiLine(false);
    bpmText->setReturnKeyStartsNewLine(false);
    bpmText->setReadOnly(false);
    bpmText->setScrollbarsShown(true);
    bpmText->setCaretVisible(false);
    bpmText->setPopupMenuEnabled(true);
    bpmText->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    bpmText->setText(TRANS("120"));

    bpmText->setBounds(61, 69, 80, 16);

    barsText.reset(new TextEditor("barsText"));
    addAndMakeVisible(barsText.get());
    barsText->setMultiLine(false);
    barsText->setReturnKeyStartsNewLine(false);
    barsText->setReadOnly(false);
    barsText->setScrollbarsShown(true);
    barsText->setCaretVisible(true);
    barsText->setPopupMenuEnabled(true);
    barsText->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
    barsText->setText(TRANS("4/4"));

    barsText->setBounds(59, 92, 80, 16);

    addChannelButton.reset(new ImageButton("addChannelButton"));
    addAndMakeVisible(addChannelButton.get());
    addChannelButton->setButtonText(TRANS("new button"));
    addChannelButton->addListener(this);

    addChannelButton->setImages(false, true, true,
                                ImageCache::getFromMemory(BinaryData::_075audiofile_png,
                                                          BinaryData::_075audiofile_pngSize), 1.0f, Colours::lightblue,
                                Image(), 1.0f, Colour(0x00000000),
                                Image(), 1.0f, Colour(0x00000000));
    addChannelButton->setBounds(456, 35, 25, 25);


    audioSettingsButton.reset(new ImageButton("audioSettingsButton"));
    addAndMakeVisible(audioSettingsButton.get());
    audioSettingsButton->setButtonText(TRANS("new button"));
    audioSettingsButton->addListener(this);

    audioSettingsButton->setImages(false, true, true,
                                   ImageCache::getFromMemory(BinaryData::_072settings_png,
                                                             BinaryData::_072settings_pngSize), 1.0f, Colours::white,
                                   Image(), 1.0f, Colour(0x00000000),
                                   Image(), 1.0f, Colour(0x00000000));
    audioSettingsButton->setBounds(456 + 42, 35, 25, 25);


    setSize(800, 130);

}

ToolbarComponent::~ToolbarComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    recordButton = nullptr;
    stopButton = nullptr;
    loopButton = nullptr;
    timeText = nullptr;
    bpmText = nullptr;
    barsText = nullptr;
    addChannelButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ToolbarComponent::paint(Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(Colour(0xff323e44));

    {
        int x = 0, y = 0, width = proportionOfWidth(1.0f), height = 100;
        Colour fillColour = Colour(0xff162f30);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.fillRect(x, y, width, height);
    }

    {
        float x = 0.0f, y = 0.0f, width = 200.0f, height = 130.0f;
        Colour fillColour = Colour(0xff162f30);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.fillRoundedRectangle(x, y, width, height, 10.0f);
    }

    {
        float x = 12.0f, y = 12.0f, width = 180.0f, height = 108.0f;
        Colour fillColour1 = Colour(0xff1d1d1d), fillColour2 = Colour(0xff292a2a);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill(ColourGradient(fillColour1,
                                         104.0f - 12.0f + x,
                                         24.0f - 12.0f + y,
                                         fillColour2,
                                         static_cast<float> (-8) - 12.0f + x,
                                         112.0f - 12.0f + y,
                                         false));
        g.fillRoundedRectangle(x, y, width, height, 10.0f);
    }

    {
        int x = 20, y = 20, width = 156, height = 18;
        String text(TRANS("Project Name"));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.setFont(Font("Calibri", 17.8f, Font::plain).withTypefaceStyle("Bold"));
        g.drawText(text, x, y, width, height,
                   Justification::bottomLeft, true);
    }

    {
        int x = 20, y = 44, width = 44, height = 18;
        String text(TRANS("Time : "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.setFont(Font("Calibri", 17.8f, Font::plain).withTypefaceStyle("Bold"));
        g.drawText(text, x, y, width, height,
                   Justification::bottomLeft, true);
    }

    {
        int x = 20, y = 68, width = 44, height = 18;
        String text(TRANS("BPM : "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.setFont(Font("Calibri", 17.8f, Font::plain).withTypefaceStyle("Bold"));
        g.drawText(text, x, y, width, height,
                   Justification::bottomLeft, true);
    }

    {
        int x = 20, y = 92, width = 36, height = 18;
        String text(TRANS("Bars : "));
        Colour fillColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.setFont(Font("Calibri", 17.8f, Font::plain).withTypefaceStyle("Bold"));
        g.drawText(text, x, y, width, height,
                   Justification::bottomLeft, true);
    }

    {
        float x = 310.0f, y = 30.0f, width = 137.0f, height = 36.0f;
        Colour fillColour = Colour(0xf2275353);
        Colour strokeColour = Colour(0xff202e2e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour(fillColour);
        g.fillRoundedRectangle(x, y, width, height, 10.0f);
        g.setColour(strokeColour);
        g.drawRoundedRectangle(x, y, width, height, 10.0f, 1.0f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ToolbarComponent::resized()
{

}

void ToolbarComponent::buttonClicked(Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == recordButton.get())
        engine.recording();

    else if (buttonThatWasClicked == stopButton.get())
        engine.stop();

    else if (buttonThatWasClicked == loopButton.get())
    {

    }
    else if (buttonThatWasClicked == addChannelButton.get())
        engine.addChannel();

    else if (buttonThatWasClicked == audioSettingsButton.get())
    {
        engine.showAudioSettings();
        engine.createTracksAndAssignInputs();
    }
}
