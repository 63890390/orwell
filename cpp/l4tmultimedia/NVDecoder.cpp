#include "NVDecoder.h"
#include "SLog.h"
#include "NaluUtils.h"

SLOG_CATEGORY("NVDecoder");

#define TEST_ERROR(condition, message, errorCode)             \
    if (condition)                                            \
    {                                                         \
        throw NVDecoderCreationException(message, errorCode); \
    }

int NVDecoder::decodeFrame(EncodedPacket &encodedPacket)
{
}
int NVDecoder::decodeFrame(EncodedPacket &encodedPacket, DecodedFrame &decodedFrame)
{
}

NVDecoder::NVDecoder(Format format, Codec codec) : format(format), codec(codec)
{
    int ret;
    TEST_ERROR(!nvVideoDecoder, "Could not create decoder", 0)

    nvApplicationProfiler.start(NvApplicationProfiler::DefaultSamplingInterval);
    nvVideoDecoder->enableProfiling();

    ret = nvVideoDecoder->subscribeEvent(V4L2_EVENT_RESOLUTION_CHANGE, 0, 0);
    TEST_ERROR(ret < 0, "Could not subscribe to V4L2_EVENT_RESOLUTION_CHANGE", ret)
    //1 = NV12, 2 = I420 TODO:?????
    if (codec==H264)
        ret = nvVideoDecoder->setOutputPlaneFormat(V4L2_PIX_FMT_H264, CHUNK_SIZE);
    else if (codec==H265)
        ret = nvVideoDecoder->setOutputPlaneFormat(V4L2_PIX_FMT_H265, CHUNK_SIZE);

    TEST_ERROR(ret < 0, "Could not set output plane format", ret)

    if (format == NALU)
    {
        ret = nvVideoDecoder->setFrameInputMode(0);
        TEST_ERROR(ret < 0, "Error in decoder setFrameInputMode for NALU", ret)
    }
    else
    {
        ret = nvVideoDecoder->setFrameInputMode(1);
        TEST_ERROR(ret < 0, "Error in decoder setFrameInputMode for CHUNK", ret)
    }
    //TODO: what's 10?
    if (outputPlaneMemType == V4L2_MEMORY_MMAP)
        ret = nvVideoDecoder->output_plane.setupPlane(V4L2_MEMORY_MMAP, 10, true, false);
    else if (outputPlaneMemType == V4L2_MEMORY_USERPTR)
        ret = nvVideoDecoder->output_plane.setupPlane(V4L2_MEMORY_USERPTR, 10, false, true);
    TEST_ERROR(ret < 0, "Error while setting up output plane", ret);

    ret = nvVideoDecoder->output_plane.setStreamStatus(true);
    TEST_ERROR(ret < 0, "Error in output plane stream on", ret);
}

void NVDecoder::prepareDecoder() {
    struct v4l2_format format;
    struct v4l2_crop crop;
    int32_t min_dec_capture_buffers;
    int ret = 0;
    uint32_t window_width;
    uint32_t window_height;
    NvBufferCreateParams input_params = {0};
    NvBufferCreateParams cParams = {0};

    // Get capture plane format from the decoder. This may change after
    // an resolution change event
    ret = nvVideoDecoder->capture_plane.getFormat(format);
    TEST_ERROR(ret < 0,
               "Error: Could not get format from decoder capture plane", ret);

    // Get the display resolution from the decoder
    ret = nvVideoDecoder->capture_plane.getCrop(crop);
    TEST_ERROR(ret < 0,
               "Error: Could not get crop from decoder capture plane", ret);

    LOG << "Video Resolution: " << crop.c.width << "x" << crop.c.height
       ;
    ctx->display_height = crop.c.height;
    ctx->display_width = crop.c.width;

    // Resolution got from the decoder
    window_width = crop.c.width;
    window_height = crop.c.height;
    
    // deinitPlane unmaps the buffers and calls REQBUFS with count 0
    nvVideoDecoder->capture_plane.deinitPlane();
    if(ctx->capture_plane_mem_type == V4L2_MEMORY_DMABUF)
    {
        for(int index = 0 ; index < ctx->numCapBuffers ; index++)
        {
            if(ctx->dmabuff_fd[index] != 0)
            {
                ret = NvBufferDestroy (ctx->dmabuff_fd[index]);
                TEST_ERROR(ret < 0, "Failed to Destroy NvBuffer", ret);
            }
        }
    }

    // Not necessary to call VIDIOC_S_FMT on decoder capture plane.
    // But decoder setCapturePlaneFormat function updates the class variables
    ret = nvVideoDecoder->setCapturePlaneFormat(format.fmt.pix_mp.pixelformat,
                                     format.fmt.pix_mp.width,
                                     format.fmt.pix_mp.height);
    TEST_ERROR(ret < 0, "Error in setting decoder capture plane format", ret);

    ctx->video_height = format.fmt.pix_mp.height;
    ctx->video_width = format.fmt.pix_mp.width;
    // Get the minimum buffers which have to be requested on the capture plane
    ret = nvVideoDecoder->getMinimumCapturePlaneBuffers(min_dec_capture_buffers);
    TEST_ERROR(ret < 0,
               "Error while getting value of minimum capture plane buffers",
               ret);

    // Request (min + 5) buffers, export and map buffers
    if(ctx->capture_plane_mem_type == V4L2_MEMORY_MMAP)
    {
        ret =
            nvVideoDecoder->capture_plane.setupPlane(V4L2_MEMORY_MMAP,
                                           min_dec_capture_buffers + 5, false,
                                           false);
        TEST_ERROR(ret < 0, "Error in decoder capture plane setup", ret);
    }
    else if(ctx->capture_plane_mem_type == V4L2_MEMORY_DMABUF)
    {
        switch(format.fmt.pix_mp.colorspace)
        {
            case V4L2_COLORSPACE_SMPTE170M:
                if (format.fmt.pix_mp.quantization == V4L2_QUANTIZATION_DEFAULT)
                {
                    LOG << "Decoder colorspace ITU-R BT.601 with standard range luma (16-235)";
                    cParams.colorFormat = NvBufferColorFormat_NV12;
                }
                else
                {
                    LOG << "Decoder colorspace ITU-R BT.601 with extended range luma (0-255)";
                    cParams.colorFormat = NvBufferColorFormat_NV12_ER;
                }
                break;
            case V4L2_COLORSPACE_REC709:
                if (format.fmt.pix_mp.quantization == V4L2_QUANTIZATION_DEFAULT)
                {
                    LOG << "Decoder colorspace ITU-R BT.709 with standard range luma (16-235)";
                    cParams.colorFormat = NvBufferColorFormat_NV12_709;
                }
                else
                {
                    LOG << "Decoder colorspace ITU-R BT.709 with extended range luma (0-255)";
                    cParams.colorFormat = NvBufferColorFormat_NV12_709_ER;
                }
                break;
            case V4L2_COLORSPACE_BT2020:
                {
                    LOG << "Decoder colorspace ITU-R BT.2020";
                    cParams.colorFormat = NvBufferColorFormat_NV12_2020;
                }
                break;
            default:
                LOG << "supported colorspace details not available, use default";
                if (format.fmt.pix_mp.quantization == V4L2_QUANTIZATION_DEFAULT)
                {
                    LOG << "Decoder colorspace ITU-R BT.601 with standard range luma (16-235)";
                    cParams.colorFormat = NvBufferColorFormat_NV12;
                }
                else
                {
                    LOG << "Decoder colorspace ITU-R BT.601 with extended range luma (0-255)";
                    cParams.colorFormat = NvBufferColorFormat_NV12_ER;
                }
                break;
        }
        ctx->numCapBuffers = min_dec_capture_buffers + 5;
        for (int index = 0; index < ctx->numCapBuffers; index++)
        {
            cParams.width = crop.c.width;
            cParams.height = crop.c.height;
            cParams.layout = NvBufferLayout_BlockLinear;
            cParams.payloadType = NvBufferPayload_SurfArray;
            cParams.nvbuf_tag = NvBufferTag_VIDEO_DEC;
            ret = NvBufferCreateEx(&ctx->dmabuff_fd[index], &cParams);
            TEST_ERROR(ret < 0, "Failed to create buffers", ret);
        }
        ret = nvVideoDecoder->capture_plane.reqbufs(V4L2_MEMORY_DMABUF,ctx->numCapBuffers);
            TEST_ERROR(ret, "Error in request buffers on capture plane", ret);
    }

    // Capture plane STREAMON
    ret = nvVideoDecoder->capture_plane.setStreamStatus(true);
    TEST_ERROR(ret < 0, "Error in decoder capture plane streamon", ret);

    // Enqueue all the empty capture plane buffers
    for (uint32_t i = 0; i < nvVideoDecoder->capture_plane.getNumBuffers(); i++)
    {
        struct v4l2_buffer v4l2_buf;
        struct v4l2_plane planes[MAX_PLANES];

        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        memset(planes, 0, sizeof(planes));

        v4l2_buf.index = i;
        v4l2_buf.m.planes = planes;
        v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        v4l2_buf.memory = ctx->capture_plane_mem_type;
        if(ctx->capture_plane_mem_type == V4L2_MEMORY_DMABUF)
            v4l2_buf.m.planes[0].m.fd = ctx->dmabuff_fd[i];
        ret = nvVideoDecoder->capture_plane.qBuffer(v4l2_buf, NULL);
        TEST_ERROR(ret < 0, "Error Qing buffer at output plane", ret);
    }
    LOG << "Query and set capture successful";
}

void NVDecoder::run()
{
    LOG << "NVDecoder::run started";
    LOG << "nvVideoDecoder->output_plane.getNumBuffers(): " << nvVideoDecoder->output_plane.getNumBuffers();
    //Counts the index of buffers we're going to fill first before dequeueing used ones
    int i = 0;
    int ret = 0;
    bool eos = false;
    /*
        We're gonna receive lots of EncodedPacket instances in the while loop below
        and extract its NALUs. Of course a NALU can end in the middle of an EncodedPacket,
        so currentEncodedPacket saves this EncodedPacket for work to continue in the offset
        currentEncodedPacketSearchPtr.
    */
    EncodedPacket currentEncodedPacket;
    //Must be null
    uint8_t *currentEncodedPacketSearchPtr = NULL;
    /*
        In this first loop we fill all the buffers, taking care to
        see if we reached EOS (in case of CHUNK format). After
        all the buffers have been setted, we start another while
        loop that blocks until a buffer can be dequeue
    */
    //TODO: what happens if shouldContinue() is setted to FALSE in the middle of the while?
    //How should I destroy things?
    while (shouldContinue())
    {
        TEST_ERROR(nvVideoDecoder->isInError(), "nvVideoDecoder->isInError() in while loop", 0)

        LOG << "-------------Gonna grab currentEncodedPacket";
        currentEncodedPacket = std::move(encodedPacketsFifo->pop_front());
        LOG << "Grabbed currentEncodedPacket";

        /*
            This is a type of configuration file that tells how the buffer should be queued
        */
        struct v4l2_buffer v4l2Buffer;
        struct v4l2_plane planes[MAX_PLANES];
        NvBuffer *nvBuffer;

        memset(&v4l2Buffer, 0, sizeof(v4l2Buffer));
        if (i < nvVideoDecoder->output_plane.getNumBuffers())
        {
            memset(planes, 0, sizeof(planes));
        }
        /*
            The buffer to where a single NALU is written. 
            As I understood, each buffer should contain a single NALU and 
            then be queued.
            I guess NvBuffer is for decoded planes too, so that's why it supports
            lots of planes. But our data is encoded (has no planes) so we only use 
            the 0th plane
        */
        if (i < nvVideoDecoder->output_plane.getNumBuffers())
            nvBuffer = nvVideoDecoder->output_plane.getNthBuffer(i);
        else
        {
            ret = nvVideoDecoder->output_plane.dqBuffer(v4l2Buffer, &nvBuffer, NULL, -1);
            TEST_ERROR(ret < 0, "Error dequeueing buffer at output plane", 0)
        }
        //Number of bytes written to nvBuffer's data pointer planeBufferPtr
        uint32_t bytesWritten = 0;
        uint8_t *planeBufferPtr = static_cast<uint8_t *>(nvBuffer->planes[0].data);
        if ((codec == H264) ||
            (codec == H265) ||
            (codec == MPEG2) ||
            (codec == MPEG4))
        {
            if (format == NALU)
            {
                /*
                    Of course we're going to fill `planeBufferPtr` with an entire NALU.
                    transferNalu returns true if an entire NALU couldn't be found
                    inside `currentEncodedPacket`, so we need to query another unit from
                    our FIFO to continue writing our NALU to `planeBufferPtr`
                */
                while (transferNalu(currentEncodedPacket.frameBuffer.get(),
                                    currentEncodedPacketSearchPtr,
                                    currentEncodedPacket.frameSize,
                                    planeBufferPtr,
                                    bytesWritten))
                {
                    currentEncodedPacket = std::move(encodedPacketsFifo->pop_front());
                }
                nvBuffer->planes[0].bytesused = bytesWritten;
            }
            else
            {
                //read_decoder_input_chunk(ctx.in_file[current_file], buffer);
            }
        }
        /*
        if (codec == VP9)
        {
            ret = read_vp9_decoder_input_chunk(&ctx, buffer);
            if (ret != 0)
                cerr << "Couldn't read VP9 chunk";
        }
        if (codec == V4L2_PIX_FMT_VP8)
        {
            ret = read_vp8_decoder_input_chunk(&ctx, buffer);
            if (ret != 0)
                cerr << "Couldn't read VP8 chunk";
        }
        */
        if (i < nvVideoDecoder->output_plane.getNumBuffers())
        {
            v4l2Buffer.index = i;
            v4l2Buffer.m.planes = planes;
        }
        v4l2Buffer.m.planes[0].bytesused = nvBuffer->planes[0].bytesused;
        /*
            Finally queries the buffer. If v4l2Buffer.m.planes[0].bytesused == 0
            the decoder understands we reached EOS (I guess)
        */
        ret = nvVideoDecoder->output_plane.qBuffer(v4l2Buffer, NULL);
        TEST_ERROR(ret < 0, "Error queueing buffer at output plane in the first while loop of run", ret)
        if (i < nvVideoDecoder->output_plane.getNumBuffers())
            i++;

        if (v4l2Buffer.m.planes[0].bytesused == 0)
        {
            LOG << "End of stream";
            eos = true;
            break;
        }
    }
}
