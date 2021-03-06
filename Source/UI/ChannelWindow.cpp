#include "ChannelWindow.h"

const int channelHeight = 70;

ChannelWindow::ChannelWindow(AudioEngine& inEngine) : engine(inEngine)
{
	startTimerHz(60);
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
    clearChannels();

    for (auto* track : engine.getTrackList())
	{
		auto audioTrack = dynamic_cast<AudioTrack*> (track);

		if (audioTrack != nullptr)
            addNewTrackComponent(*audioTrack);
	}
}

void ChannelWindow::clearChannels()
{
    channels.clear();
    channelY = 0;
}

void ChannelWindow::addNewTrackComponent(AudioTrack& audioTrack)
{
    channels.emplace_back();

    auto& addedChannel = channels.back();

    addedChannel.reset(new ChannelComponent(engine, audioTrack));
    addAndMakeVisible(*addedChannel);
	

    addedChannel->setBounds(0, channelY, getWidth(), channelHeight);
    channelY += channelHeight;
}