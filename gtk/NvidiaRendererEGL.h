#ifndef NvidiaRendererEGL_H
#define NvidiaRendererEGL_H
#include "NvEglRenderer.h"
#include "DecodedFrame.h"
#include "ThreadSafeDeque.h"
#include "Stoppable.h"
#include <memory>
#include "Profiler.h"
#include "Renderer.h"

class NvidiaRendererEGL: public Stoppable, public Renderer {
public:
    NvidiaRendererEGL();
    NvidiaRendererEGL(int width, int height, int x, int y);
    void setDecodedFramesFifo(std::shared_ptr<ThreadSafeDeque<std::shared_ptr<DecodedFrame>>> decodedFramesFifo)
	{
		this->decodedFramesFifo = decodedFramesFifo;
	}
    void run();
    //std::unique_ptr<NvEglRenderer> renderer;
    //TODO: change back to smart pointer
    NvEglRenderer* renderer;
    static int count;
protected:
    std::shared_ptr<ThreadSafeDeque<std::shared_ptr<DecodedFrame>>> decodedFramesFifo;
};
#endif //NvidiaRendererEGL_H