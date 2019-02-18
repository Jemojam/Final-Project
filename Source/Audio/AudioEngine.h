#pragma once

#include "JuceHeader.h"


using namespace tracktion_engine;
namespace te = tracktion_engine;

class AudioEngine
{
public :

    AudioEngine();
    ~AudioEngine();

    void addChannel();
    void removeChannel();
    void removeTrack(te::AudioTrack& track);
    void play();
    void stop();
    void pause();

    bool isPlaying();

    bool isDirty() { return dirty; }

    void setDirty(bool inDirty) { dirty = inDirty; }

    TrackList& getTrackList() { return edit->getTrackList(); }

	void changeVolume(AudioTrack& track, float newVolume);

    void addNewClipFromFile(const File& editFile, AudioTrack& track);

	void showAudioSettings();

private:

    te::WaveAudioClip::Ptr loadAudioFileAsClip(const File& file, AudioTrack& track);
    void removeAllClips(te::AudioTrack& track);

    void adjustClipProperties(tracktion_engine::WaveAudioClip& clip) const;

    te::Engine engine{ProjectInfo::projectName};

    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> playSource;

    std::unique_ptr<te::Edit> edit;
	std::unique_ptr < te::VolumeAndPanPlugin> volumeAndPanPlugin;

    bool dirty = true;
    int trackNum = 0;
    void removeAllTracks();

    TransportControl& getTransport() const;
    void addVolumeAndPanPlugin(AudioTrack& track) const;
	
	AudioDeviceManager audioDeviceManagerTool;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEngine)
};