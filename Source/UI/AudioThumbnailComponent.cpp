

#include "AudioThumbnailComponent.h"

AudioThumbnailComponent::AudioThumbnailComponent(tracktion_engine::Clip& inClip) :
        clip(inClip),
        thumbnailCache(5), thumbnail(512, formatManager, thumbnailCache)
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
    Rectangle<int> thumbnailBounds(200, 70);

    if (thumbnail.getNumChannels() == 0)
        paintIfNoFileLoaded(g, thumbnailBounds);
    else
        paintIfFileLoaded(g, thumbnailBounds);
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
    //g.fillRect(thumbnailBounds);

    g.drawFittedText("", thumbnailBounds, Justification::centred, 1.0f);
}

void AudioThumbnailComponent::paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds)
{
    g.fillAll(Colours::ghostwhite);
    g.setColour(Colours::blue);
    //g.fillRect(thumbnailBounds);
    //auto thumbArea = getLocalBounds();

    thumbnail.drawChannels(g, thumbnailBounds, 0.0, thumbnail.getTotalLength(), 1.0f);
}

void AudioThumbnailComponent::initSource()
{
    File file = clip.getCurrentSourceFile();
    thumbnail.setSource(new FileInputSource(file));

}

