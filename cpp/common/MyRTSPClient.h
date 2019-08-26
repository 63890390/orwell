#ifndef MyRTSPCLient_H
#define MyRTSPCLient_H
#include <iostream>
#include "Decoder.h"
#include "rtspClient.h"
#include "FrameUpdater.h"
#include "VideoReceiver.h"
#include "VideoRecorder.h"
#include "EncodedFrame.h"
#include "Stoppable.h"
#include "RTSPClient.h"
/*
    RTSP client that uses MyRtspClient library
*/
class MyRTSPClient : public RTSPClient
{
public:
    RtspClient myRtspClient;
    MyRTSPClient(std::string uri);

    int init();
    void run();
    int receivePacket();

private:
    bool firstConnection = true;
    std::shared_ptr<ThreadSafeDeque<EncodedFrame>> encodedFramesFifo;
    //void ByeFromServerClbk();
};
#endif // MyRTSPCLient_H
