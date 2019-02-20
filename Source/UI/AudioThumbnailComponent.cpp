

#include "AudioThumbnailComponent.h"

	AudioThumbnailComponent::AudioThumbnailComponent(AudioEngine & inEngine, AudioFormatManager& formatManager) : engine(inEngine), thumbnailCache(5), thumbnail(512, formatManager, thumbnailCache)
	{
		formatManager.registerBasicFormats();
		thumbnail.addChangeListener(this);
	}

	AudioThumbnailComponent::~AudioThumbnailComponent()
	{
	}

	void AudioThumbnailComponent::paint(Graphics& g)
	{
		Rectangle<int> thumbnailBounds(10, 100, getWidth() - 20, getHeight() - 120);

		if (thumbnail.getNumChannels() == 0)
			paintIfNoFileLoaded(g, thumbnailBounds);
		else
			paintIfFileLoaded(g, thumbnailBounds);
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

	void AudioThumbnailComponent::paintIfNoFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds)
	{
		g.setColour(Colours::darkgrey);
		g.fillRect(thumbnailBounds);
		g.setColour(Colours::white);
		g.drawFittedText("", thumbnailBounds, Justification::centred, 1.0f);
	}

	void AudioThumbnailComponent::paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds)
	{
		g.setColour(Colours::white);
		g.fillRect(thumbnailBounds);

		g.setColour(Colours::red);                                     // [8]

		thumbnail.drawChannels(g,                                      // [9]
			thumbnailBounds,
			0.0,                                    // start time
			thumbnail.getTotalLength(),             // end time
			1.0f);                                  // vertical zoom
	}

    void AudioThumbnailComponent::setSourceThumbnail(File& file)
    {
		
		thumbnail.setSource (new FileInputSource (file));

    }

