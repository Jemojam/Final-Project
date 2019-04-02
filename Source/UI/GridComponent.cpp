
#include "GridComponent.h"

GridComponent::GridComponent () 
{
	gridview.setScrollBarsShown(true, true, true, true);
	addAndMakeVisible(gridview);

    setSize (600, 400);


}

GridComponent::~GridComponent()
{

}


void GridComponent::paint (Graphics& g)
{


    g.fillAll (Colours::transparentBlack);
	gridview.setBounds(0, 0, 600, 600);


}

void GridComponent::resized()
{

}

