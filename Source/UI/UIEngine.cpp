#include "UIEngine.h"

constexpr int toolBarHeight = 130;

constexpr int yOfGrid = 100;
constexpr int xOfGrid = 200;

UIEngine::UIEngine(AudioEngine& inEngine) :
    toolbar(inEngine),
    channelWindow(inEngine),
    engine(inEngine)
{
    addAndMakeVisible(toolbar);
    addAndMakeVisible(channelWindow);
	//addAndMakeVisible(gridWindow);

}

void UIEngine::resized()
{
    toolbar.setBounds(0, 0, getWidth(), toolBarHeight);
    channelWindow.setBounds(getLocalBounds().withTrimmedTop(toolBarHeight));
	gridWindow.setBounds(xOfGrid, yOfGrid, proportionOfWidth(1.0f), proportionOfHeight(1.0f));
}
