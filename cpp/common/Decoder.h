#ifndef Decoder_H
#define Decoder_H
#include <vector>
#include <thread>
#include <iostream>
#include <memory>
#include "EncodedPacket.h"
#include "DecodedFrame.h"
#include "ThreadSafeDeque.h"
#include "Stoppable.h"
#include <functional>

class Decoder: public Stoppable
{
public:
	enum Codec
	{
		H264,
		H265,
		MPEG2,
		MPEG4,
		VP9
	} codec;
	/*
		Thread loop that continuously pushes data from encodedPacketsFifo and decoded it
	*/
	virtual void run();
	/* 
		Decodes to CPU memory. 
		If invoked in a FfmpegSoftwareDecoder instance, it'll simply do
		all the process in software.
		If invoked in a FfmpegHardwareDecoder, it'll decode in hardware,
		then copy from GPU memory to CPU memory.
		To just decode to GPU memory but not get it in CPU memory, use
		FfmpegHardwareDecoder::hardwareDecode().
		
		- frameBuffer contains RAW undecoded video
		- frameLength contains size of frameBuffer
		- frame is the pointer to the decoded frame data
	*/
	virtual int sendPacket(std::shared_ptr<EncodedPacket> encodedPacket, std::shared_ptr<DecodedFrame> decodedFrame) {};
	/*
		Decodes directly to the decodedFramesFifo
	*/
	virtual int sendPacket(std::shared_ptr<EncodedPacket> encodedPacket) {};
	
	/*
	void setEncodedPacketsFifo(std::shared_ptr<ThreadSafeDeque<std::shared_ptr<EncodedPacket>>> encodedPacketsFifo)
	{
		this->encodedPacketsFifo = encodedPacketsFifo;
	}
	
	void setDecodedFramesFifo(std::shared_ptr<ThreadSafeDeque<std::shared_ptr<DecodedFrame>>> decodedFramesFifo)
	{
		this->decodedFramesFifo = decodedFramesFifo;
	}
	*/
	virtual void startThreadMode() {
		runThread = std::thread(&Decoder::run, this);
	}

	virtual void setOnAcquireNewPacket(std::function<std::shared_ptr<EncodedPacket>()> onAcquireNewPacket) {
		this->onAcquireNewPacket = onAcquireNewPacket;
	}

	virtual void setOnNewDecodedFrame(std::function<void(std::shared_ptr<DecodedFrame>)> onNewDecodedFrame) {
		this->onNewDecodedFrame = onNewDecodedFrame;
	}

protected:
	/*
		Here we store a pointer to our FIFOs, which are made of a simple thread-safe 
		deque implementation called ThreadSafeDeque
	*/
	//std::shared_ptr<ThreadSafeDeque<std::shared_ptr<EncodedPacket>>> encodedPacketsFifo;
	//std::shared_ptr<ThreadSafeDeque<std::shared_ptr<DecodedFrame>>> decodedFramesFifo;
	std::thread runThread;
	std::function<std::shared_ptr<EncodedPacket>()> onAcquireNewPacket;
	std::function<void(std::shared_ptr<DecodedFrame>)> onNewDecodedFrame;
};

#endif // Decoder_H
