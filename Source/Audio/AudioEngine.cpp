#include "AudioEngine.h"
#include <typeinfo>


using namespace tracktion_engine;

AudioEngine::AudioEngine()
{
	edit = std::make_unique<Edit>(engine, createEmptyEdit(), Edit::forEditing, nullptr, 0);

	removeAllTracks();

    for (auto track : getTrackList())
    {
        auto plugins = track->getAllPlugins();

//        juce::PluginDescription description;
//
//        auto newPlugin = edit->getPluginCache().createNewPlugin("volume", description);
//
//        plugins.add(newPlugin);
    }
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
		if (trackNum - 1 == 0)
		{
			auto track = edit->getOrInsertAudioTrackAt(--trackNum);
			removeTrack(*track);
		}
		else
		{
			auto track = edit->getOrInsertAudioTrackAt(--trackNum);
			removeTrack(*track);
		}
	}
}

void AudioEngine::removeTrack(te::AudioTrack & track)
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

        EditTimeRange timeRange(0.0, audioFile.getLength());
        ClipPosition position = {timeRange, 0.0};

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
		adjustClipProperties(*clip);
}

void AudioEngine::play()
{
	auto& transport = edit->getTransport();

	transport.setLoopRange({ 0.0, edit->getLength() });
	transport.looping = true;
	transport.play(false);

}

void AudioEngine::removeAllClips(te::AudioTrack & track)
{
	auto& clips = track.getClips();

	for (int i = clips.size(); --i >= 0;)
		clips.getUnchecked(i)->removeFromParentTrack();
}

void AudioEngine::adjustClipProperties(tracktion_engine::WaveAudioClip & clip) const
{
	// Disable auto tempo and pitch, we'll handle these manually
	clip.setAutoTempo(false);
	clip.setAutoPitch(false);
	clip.setTimeStretchMode(TimeStretcher::defaultMode);
}

void AudioEngine::addChannel()
{
	auto numTracks = edit->getTrackList().size();

	edit->getOrInsertAudioTrackAt(numTracks);

	dirty = true;
}

void AudioEngine::changeVolume(AudioTrack& track, float newVolume)
{
    auto plugins = track.getAllPlugins();

    for (int index = 0; index < plugins.size(); ++index)
    {
        auto plugin = plugins.getObjectPointer(index);

        auto volume = dynamic_cast<VolumeAndPanPlugin*>(plugin);

        if (volume != nullptr)
        {
            auto db = volumeFaderPositionToDB(newVolume);
            volume->setVolumeDb(db);
        }
    }
}