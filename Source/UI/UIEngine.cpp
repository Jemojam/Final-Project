#include "UIEngine.h"

constexpr int toolBarHeight = 130;

UIEngine::UIEngine(AudioEngine& inEngine) :
    engine(inEngine),
    toolbar(inEngine),
    channelWindow(inEngine)
{
    addAndMakeVisible(toolbar);
    addAndMakeVisible(channelWindow);
}

UIEngine::~UIEngine()
{
}

void UIEngine::paint(Graphics& g)
{
}

void UIEngine::resized()
{
    toolbar.setBounds(0, 0, getWidth(), toolBarHeight);

    channelWindow.setBounds(getLocalBounds().withTrimmedTop(toolBarHeight));
}
