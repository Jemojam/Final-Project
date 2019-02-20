


#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"
//==============================================================================
class AudioThumbnailComponent   : public Component,
                                  private ChangeListener
{
public:
	AudioThumbnailComponent(AudioEngine & inEngine);
	~AudioThumbnailComponent();

    void paint (Graphics& g) override;
    void changeListenerCallback (ChangeBroadcaster* source) override;

	void setSourceThumbnail(File& file);
	
private:

    void thumbnailChanged();
	void paintIfNoFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds);
	void paintIfFileLoaded(Graphics & g, const Rectangle<int>& thumbnailBounds);

	AudioFormatManager formatManager;
    AudioThumbnailCache thumbnailCache; 
    AudioThumbnail thumbnail; 

	AudioEngine& engine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioThumbnailComponent)
};
