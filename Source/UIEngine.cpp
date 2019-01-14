#include "UIEngine.h"

UIEngine::UIEngine()
{
	addAndMakeVisible(toolbar);
	setSize(getParentWidth(),getParentHeight());
	
}

UIEngine::~UIEngine()
{
}

void UIEngine::paint(Graphics & g)
{
}

void UIEngine::resized()
{
	
}

void UIEngine::addNewChannel()
{
	/*std::unique_ptr<ChannelComponent> channel;
	channels.push_back(channel);
	//channels.add(channel);
	//postioning the channels
	int newY = channels.size() * 80;
	channel->setBounds(0, newY, channel->getWidth(), channel->getHeight());
	addAndMakeVisible(*channel);*/
}
