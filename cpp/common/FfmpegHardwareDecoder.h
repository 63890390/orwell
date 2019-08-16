#ifndef HardwareFfmpegDecoder_H
#define HardwareFfmpegDecoder_H
#include "FfmpegDecoder.h"
//Extern C is absolutely needed!
extern "C"
{
#include <libavutil/hwcontext.h>
#include <libavutil/imgutils.h>
}

class FfmpegHardwareDecoder: public FfmpegDecoder {
    public:
        enum Device{SOFTWARE, HARDWARE} device;
        static std::vector<std::string> getSupportedDevices();
        FfmpegHardwareDecoder(Codec codec, Device device, std::string hardwareType):device(device), hardwareType(hardwareType){
            this->codec = codec;
        };
        
        int init();
        //Decodes to GPU memory but not get it back to CPU memory
        int hardwareDecode(uint8_t* frameBuffer, int frameLength);
        /* 
            Calls hardwareDecode() then gets video from GPU memory to CPU memory and 
            sends to VideoReceiver instance.
        */
        int decodeFrame(uint8_t* frameBuffer, int frameLength);
        int decodeFrame(uint8_t* frameBuffer, int frameLength, Frame& frame);
        //
        AVPixelFormat print_avaliable_pixel_formats_for_hardware(struct AVCodecContext *avctx, const AVPixelFormat *fmt);
        AVPixelFormat get_format(struct AVCodecContext *s, const AVPixelFormat *fmt);

        ~FfmpegHardwareDecoder(){
            av_frame_free(&decodedAvFrame);
            //av_frame_free(&fromGPUAvFrame);
            avcodec_free_context(&avCodecContext);
            av_buffer_unref(&avBufferRef);
            //av_freep(&buffer);
        }
    private:
    	AVBufferRef 	*avBufferRef;
        AVFrame         *decodedAvFrame = NULL;
        //AVFrame         *fromGPUAvFrame = NULL;
        AVFrame         *tmp_frame = NULL;
        AVPacket         avPacket;
        //Image from GPU memory gets stored here
        uint8_t         *buffer = NULL;
        AVPixelFormat    avPixelFormat;
        std::string      hardwareType;
};

#endif //HardwareFfmpegDecoder_H