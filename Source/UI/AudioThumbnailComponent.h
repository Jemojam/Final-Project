#pragma once

#include "JuceHeader.h"
#include "Audio/AudioEngine.h"

//==============================================================================
class AudioThumbnailComponent : public Component,
                                private ChangeListener
{
public:
    explicit AudioThumbnailComponent(tracktion_engine::Clip& inClip);
    ~AudioThumbnailComponent();

    void paint(Graphics& g) override;
    void changeListenerCallback(ChangeBroadcaster* source) override;

    Clip& getClip() { return clip; }
private:

    void initSource();
    void thumbnailChanged();
    void paintIfNoFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds);
    void paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds);

    AudioFormatManager formatManager;
    AudioThumbnailCache thumbnailCache;
    AudioThumbnail thumbnail;

    tracktion_engine::Clip& clip;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioThumbnailComponent)
};
