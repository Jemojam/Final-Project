

#include "AudioThumbnailComponent.h"

AudioThumbnailComponent::AudioThumbnailComponent(tracktion_engine::Clip& inClip) :
        thumbnailCache(5), thumbnail(512, formatManager, thumbnailCache),
        clip(inClip)
{
    formatManager.registerBasicFormats();
    thumbnail.addChangeListener(this);
    initSource();
}

AudioThumbnailComponent::~AudioThumbnailComponent()
{
    thumbnail.removeChangeListener(this);
}

void AudioThumbnailComponent::paint(Graphics& g)
{
	Rectangle<int> thumbnailBounds(200 *1, 70);
	if (!selected)
	{
		thumbnailBounds.setSize(200 * clip.getMaximumLength(), 70);
	}
	else
	{
		thumbnailBounds.~Rectangle();
	}
    

    if (thumbnail.getNumChannels() == 0)
        paintIfNoFileLoaded(g, thumbnailBounds);
    else
        paintIfFileLoaded(g, thumbnailBounds);

	if (selected)
	{
		g.setColour(Colours::purple);
		g.drawRect(thumbnailBounds, 1);
	}
}



void AudioThumbnailComponent::changeListenerCallback(ChangeBroadcaster* source)
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
    g.fillAll(Colours::red);
    g.drawFittedText("", thumbnailBounds, Justification::centred, 1);
}

void AudioThumbnailComponent::paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds)
{
    //g.fillAll(Colours::darkslategrey);
	g.setColour(Colours::darkslategrey);
	g.fillRect(thumbnailBounds);
	
    g.setColour(Colours::darkorange);

    thumbnail.drawChannels(g, thumbnailBounds, 0.0, thumbnail.getTotalLength(), 1.0f);
	
}



void AudioThumbnailComponent::mouseDown(const MouseEvent& /*event*/)
{
	selected = !selected;
	repaint();
	clip.removeFromParentTrack();
	
}

void AudioThumbnailComponent::initSource()
{
    File file = clip.getCurrentSourceFile();
    thumbnail.setSource(new FileInputSource(file));

}

