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
	TrackList& getTrackList() { return edit->getTrackList(); }
	void addNewClipFromFile(const File& editFile, AudioTrack& track);

	void changeVolume(AudioTrack& track, float newVolume);
	void muteChannel(AudioTrack& track);
	void soloChannel(AudioTrack& track);
	
	
	void selectedChannel(AudioTrack& track, bool selected);



    void play();
    void stop();
    void pause();
    bool isPlaying();

	void recording();

	


	//void startRecording();

	//void stopRecording();

	void showAudioSettings();
	void audioSettings();

	TransportControl& AudioEngine::getTransport() const;

	bool isDirty() { return dirty; }
	void setDirty(bool inDirty) { dirty = inDirty; }
private:
	//============================private functions========================================
    te::WaveAudioClip::Ptr loadAudioFileAsClip(const File& file, AudioTrack& track);
    void removeAllClips(te::AudioTrack& track);
    void adjustClipProperties(tracktion_engine::WaveAudioClip& clip) const;
	void removeAllTracks();
	void addVolumeAndPanPlugin(AudioTrack& track) const;
	te::AudioTrack* getOrInsertAudioTrackAt(te::Edit& edit, int index);
	void armTrack(te::AudioTrack& t, bool arm, int position);
	bool isTrackArmed(te::AudioTrack& t, int position);

	void toggleRecord();
	//============================private objects========================================
    te::Engine engine{ProjectInfo::projectName};
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> playSource;
    std::unique_ptr<te::Edit> edit;
	
	std::unique_ptr <te::VolumeAndPanPlugin> volumeAndPanPlugin;
	AudioDeviceManager audioDeviceManagerTool;

	//std::unique_ptr <AudioRecorder> audioRecorder;

	bool channelSelected = false;
    bool dirty = true;
    int trackNum = 0;

	File lastRecording;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEngine)
};