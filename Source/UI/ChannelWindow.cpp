#include "ChannelWindow.h"

const int channelHeight = 70;

ChannelWindow::ChannelWindow(AudioEngine& inEngine) : engine(inEngine)
{
	startTimerHz(60);
}

void ChannelWindow::paint(Graphics& g)
{

}

void ChannelWindow::timerCallback()
{
	if (engine.isDirty())
	{
		rebuildTrackList();
		engine.setDirty(false);
	}

}

void ChannelWindow::rebuildTrackList()
{
	auto& trackList = engine.getTrackList();

	channels.clear();

	int channelY = 0;

	for (auto& track : trackList)
	{
		channels.emplace_back();

		auto& addedChannel = channels.back();

		auto audioTrack = dynamic_cast<AudioTrack*> (track);

		if (audioTrack != nullptr)
        {
            addedChannel = std::make_unique<ChannelComponent>(engine, *audioTrack);
            addAndMakeVisible(*addedChannel);

            addedChannel->setBounds(0, channelY, getWidth(), channelHeight);
            channelY += channelHeight;
        }
	}
}