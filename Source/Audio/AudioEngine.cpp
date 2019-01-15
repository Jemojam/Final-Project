#include "AudioEngine.h"

using namespace tracktion_engine;

AudioEngine::AudioEngine()
{
	edit = std::make_unique<Edit>(engine, createEmptyEdit(), Edit::forEditing, nullptr, 0);

	removeAllTracks();
}

void AudioEngine::removeAllTracks()
{
	for (auto track: getTrackList())
	{
		edit->deleteTrack(track);
	}
}

AudioEngine::~AudioEngine()
{
	engine.getTemporaryFileManager().getTempDirectory().deleteRecursively();
}

void AudioEngine::addChannel(File file)
{
	addNewClipFromFile(file, trackNum++);
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

te::WaveAudioClip::Ptr AudioEngine::loadAudioFileAsClip(const File & file, int trackNumber)
{
	auto track = edit->getOrInsertAudioTrackAt(trackNumber);

	if (track != nullptr)
	{
		//removeAllClips(*track);

		// Add a new clip to this track
		AudioFile audioFile(file);

		if (audioFile.isValid())
		{
			auto name = file.getFileNameWithoutExtension();

			EditTimeRange timeRange(0.0, audioFile.getLength());
			ClipPosition position = { timeRange, 0.0 };

			auto newClip = track->insertWaveClip(name, file, position, false);

			if (newClip != nullptr)
				return newClip;
		}
		return nullptr;
	}
}

void AudioEngine::addNewClipFromFile(const File & editFile, int trackNum)
{
	auto clip = loadAudioFileAsClip(editFile, trackNum);

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
