#include "UIEngine.h"

constexpr int toolBarHeight = 130;

UIEngine::UIEngine(AudioEngine& inEngine) :
    engine(inEngine),
    toolbar(inEngine),
    channelWindow(inEngine)
{
    addAndMakeVisible(toolbar);
    addAndMakeVisible(channelWindow);
	addAndMakeVisible(gridWindow);

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
	gridWindow.setBounds(200, 140, 400, 400);
}
