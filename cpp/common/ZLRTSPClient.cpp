#include "ZLRTSPClient.h"
#include "SLog.h"

int ZLRTSPClient::init()
{
    weak_ptr<MediaPlayer> weakPlayer = player;
    player->setOnPlayResult([weakPlayer, this](const SockException &ex) {
        this->LOG << "OnPlayResult:" << ex.what() << " for " << this->uri;
        auto strongPlayer = weakPlayer.lock();
        if (ex || !strongPlayer)
        {
            return;
        }

        auto viedoTrack = strongPlayer->getTrack(TrackVideo);
        if (!viedoTrack)
        {
            this->LOG << "No video track for " << this->uri;
            return;
        }
        viedoTrack->addDelegate(std::make_shared<FrameWriterInterfaceHelper>([this](const Frame::Ptr &frame) {
            if (!this->encodedPacketsFifo)
			{
				//LOG(SLog::CRITICAL_ERROR) << "MyRTSPClient: no encodedPacketsFifo setted, nowhere to send RTSP data!" << this->uri;
			}
			else
			{
				//this->encodedPacketsFifo->emplace_back(std::move(frame));
                this->LOG << "encodedPacketsFifo emplace!";
			}
        }));
    });

    player->setOnShutdown([](const SockException &ex) {
        ErrorL << "OnShutdown:" << ex.what();
    });
}