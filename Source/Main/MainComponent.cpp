#include "MainComponent.h"

MainComponent::MainComponent(): ui(engine)
{
	addAndMakeVisible(ui);

    setSize (800, 600);
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    ui.setBounds(getLocalBounds());
}
