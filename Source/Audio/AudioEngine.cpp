#include "AudioEngine.h"


AudioEngine::AudioEngine()
{
    edit = std::make_unique<Edit>(engine, createEmptyEdit(), Edit::forEditing, nullptr, 0);

    removeAllTracks();
}

AudioEngine::~AudioEngine()
{
    engine.getTemporaryFileManager().getTempDirectory().deleteRecursively();
}

void AudioEngine::removeAllTracks()
{
    for (auto track : getTrackList())
    {
        edit->deleteTrack(track);
    }
}

void AudioEngine::removeChannel()
{
    if (trackNum > 0)
    {
        auto track = getOrInsertAudioTrackAt(*edit,--trackNum);
        removeTrack(*track);
    }
}

te::AudioTrack* AudioEngine::getOrInsertAudioTrackAt(te::Edit& edit, int index)
{
	edit.ensureNumberOfAudioTracks(index + 1);
	return te::getAudioTracks(edit)[index];
}

void AudioEngine::removeTrack(te::AudioTrack& track)
{
    auto& clips = track.getClips();

    clips.getUnchecked(trackNum)->removeFromParentTrack();
}

te::WaveAudioClip::Ptr AudioEngine::loadAudioFileAsClip(const File& file, AudioTrack& track)
{
    // Add a new clip to this track
    AudioFile audioFile(file);

    if (audioFile.isValid())
    {
        auto name = file.getFileNameWithoutExtension();
		
		EditTimeRange timeRange(0, audioFile.getLength());
		ClipPosition position = { timeRange, 0 };

		auto newClip = track.insertWaveClip(name, file, position, false);

		if (newClip != nullptr)
			return newClip;
	
    }

    return nullptr;
}

void AudioEngine::addNewClipFromFile(const File& editFile, AudioTrack& track)
{
    auto clip = loadAudioFileAsClip(editFile, track);

	if (clip != nullptr)
	{
		clip = loadAudioFileAsClip(editFile, track);
		adjustClipProperties(*clip);
	}
        
}

void AudioEngine::selectedChannel(AudioTrack & track, bool selected)
{
	track.selectionStatusChanged((selected) ? true : false);

}

void AudioEngine::play()
{
    getTransport().setLoopRange({0.0, edit->getLength()});
    getTransport().looping = true;
    getTransport().play(false);

}
TransportControl& AudioEngine::getTransport() const { return edit->getTransport(); }

void AudioEngine::stop()
{
    getTransport().stop(true, false, true, true);
}

void AudioEngine::pause()
{
    getTransport().stop(true, false, true, false);
}

/*
void AudioEngine::recording()
{
	audioRecorder->startRecording(lastRecording);
}


void AudioEngine::startRecording()
{
	auto parentDir = File::getSpecialLocation(File::userDocumentsDirectory);
	lastRecording = parentDir.getNonexistentChildFile("clip", ".wav");
	audioRecorder->startRecording(lastRecording);
}

void AudioEngine::stopRecording()
{
	audioRecorder->stop();

	lastRecording = File();
}

*/


void AudioEngine::removeAllClips(te::AudioTrack& track)
{
    auto& clips = track.getClips();

    for (int i = clips.size(); --i >= 0;)
        clips.getUnchecked(i)->removeFromParentTrack();
}

void AudioEngine::adjustClipProperties(tracktion_engine::WaveAudioClip& clip) const
{
    // Disable auto tempo and pitch, we'll handle these manually
    clip.setAutoTempo(false);
    clip.setAutoPitch(false);
    clip.setTimeStretchMode(TimeStretcher::defaultMode);
}

void AudioEngine::addChannel()
{
    auto numTracks = edit->getTrackList().size();
    auto track = getOrInsertAudioTrackAt(*edit, numTracks-1);

    addVolumeAndPanPlugin(*track);

    dirty = true;
}

void AudioEngine::addVolumeAndPanPlugin(AudioTrack& track) const
{
    auto plugins = track.getAllPlugins();

    PluginDescription description;
    auto newPlugin = edit->getPluginCache().createNewPlugin("volume", description);

    plugins.add(newPlugin);
}

void AudioEngine::changeVolume(AudioTrack& track, float newVolume)
{
    auto plugins = track.getAllPlugins();

    for (int index = 0; index < plugins.size(); ++index)
    {
        auto plugin = plugins.getObjectPointer(index);

        auto volume = dynamic_cast<VolumeAndPanPlugin*>(plugin);

        if (volume != nullptr)
            volume->setVolumeDb(newVolume);
    }
}

void AudioEngine::muteChannel(AudioTrack & track)
{
	if (track.isMuted(false))
	{
		track.setMute(false);
	}
	else
	{
		track.setMute(true);
	}
}

void AudioEngine::soloChannel(AudioTrack & track)
{
	if (track.isSolo(true))
	{
		track.setSolo(false);
	}
	else
	{
		track.setSolo(true);
	}
}


bool AudioEngine::isPlaying()
{
    return getTransport().isPlaying();
}


void AudioEngine::showAudioSettings()
{
	audioSettings();
}

void AudioEngine::audioSettings()
{
	DialogWindow::LaunchOptions o;
	o.dialogTitle = TRANS("Audio Settings");
	o.dialogBackgroundColour = LookAndFeel::getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId);
	o.content.setOwned(new AudioDeviceSelectorComponent(audioDeviceManagerTool, 2, 2, 0, 2, false, false, true, true));
	o.content->setSize(400, 600);
	o.launchAsync();
}
