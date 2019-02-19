

#include "AudioThumbnailComponent.h"

	AudioThumbnailComponent::AudioThumbnailComponent(AudioEngine & inEngine, AudioFormatManager& formatManager) : engine(inEngine), thumbnailCache(5), thumbnail(512, formatManager, thumbnailCache)
	{
		formatManager.registerBasicFormats();
		thumbnail.addChangeListener(this);
	}

	AudioThumbnailComponent::~AudioThumbnailComponent()
	{
	}

	void AudioThumbnailComponent::paint (Graphics& g)
    {
        Rectangle<int> thumbnailBounds (10, 100, getWidth() - 20, getHeight() - 120);

        if (thumbnail.getNumChannels() != 0)
                paintLoadedFile (g, thumbnailBounds);
    }


    void AudioThumbnailComponent::changeListenerCallback (ChangeBroadcaster* source)
    {
        if (source == &thumbnail)       
			thumbnailChanged();
    }

    void AudioThumbnailComponent::thumbnailChanged()
    {
        repaint();
    }

    void AudioThumbnailComponent::paintLoadedFile (Graphics& g, const Rectangle<int>& thumbnailBounds)
    {
        g.setColour (Colours::transparentWhite);
        g.fillRect (thumbnailBounds);

        g.setColour (Colours::aqua);                                    

        thumbnail.drawChannels (g, thumbnailBounds, 0.0, thumbnail.getTotalLength(), 1.0f);                                  
    }

    void AudioThumbnailComponent::setSourceThumbnail(File& file)
    {
		
		thumbnail.setSource (new FileInputSource (file));

    }

