#include "UIEngine.h"

constexpr int toolBarHeight = 130;

constexpr int yOfGrid = 100;
constexpr int xOfGrid = 200;

UIEngine::UIEngine(AudioEngine& inEngine) :
    toolbar(inEngine),
    channelWindow(inEngine),
    engine(inEngine),
	playhead(inEngine)
{
    addAndMakeVisible(toolbar);
    addAndMakeVisible(channelWindow);
	addAndMakeVisible(playhead);
	
	//addAndMakeVisible(viewport);	
	//viewport.setScrollBarsShown(true, true, false, false);
	//viewport.setViewedComponent(&channelWindow);
	//viewport.setViewedComponent(&playhead);

}

void UIEngine::resized()
{
	auto width = proportionOfWidth(1.0f);
	viewport.setBounds(0, toolBarHeight, width, 500);
    toolbar.setBounds(0, 0, getWidth(), toolBarHeight);
    channelWindow.setBounds(getLocalBounds().withTrimmedTop(toolBarHeight));
	gridWindow.setBounds(xOfGrid, yOfGrid, proportionOfWidth(1.0f), proportionOfHeight(1.0f));
	playhead.setBounds(getLocalBounds().withTrimmedTop(toolBarHeight).withTrimmedLeft(200));
}

