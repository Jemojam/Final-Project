#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChannelWindow.h"


class GridComponent  : public Component
{
public:
  
    GridComponent ();
    ~GridComponent();

    void paint (Graphics& g) override;
    void resized() override;



private:

	
	Viewport gridview;
	






	//ChannelWindow channelWindow;
	/*
	DragAndDropContainer dragAndDropContainer; //<=================== unique_ptr?
	std::unique_ptr<DragAndDropTarget> dragAndDropTarget;
	std::unique_ptr<AudioPlayHead> audioPlayHead;
	std::unique_ptr<AudioThumbnailComponent> audioThumbnailComponent;
	//AudioThumbnailComponent audiothumbnailcomponent; //need to creat deafult constracor
	*/
	


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GridComponent)
};
