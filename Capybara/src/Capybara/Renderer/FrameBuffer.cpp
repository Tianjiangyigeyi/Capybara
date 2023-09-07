#include "precomp.h"
#include "FrameBuffer.h"

#include "Capybara/Platform/OpenGL/OpenGLFramebuffer.h"

namespace Capybara
{
    FrameBuffer* FrameBuffer::Create(uint32_t width, uint32_t height, FrameBufferFormat format)
    {
        FrameBuffer* result = nullptr;

        switch (RendererAPI::Current())
        {
        case RendererAPIType::None: return nullptr;
        case RendererAPIType::OpenGL: result = new OpenGLFrameBuffer(width, height, format);
        }
        FrameBufferPool::GetGlobal()->Add(result);
        return result;
    }

    FrameBufferPool* FrameBufferPool::s_Instance = new FrameBufferPool;
    FrameBufferPool::FrameBufferPool(uint32_t maxFBs /* = 32 */)
    {

    }

    FrameBufferPool::~FrameBufferPool()
    {
        
    }

    std::weak_ptr<FrameBuffer> FrameBufferPool::AllocateBuffer()
    {
        return std::weak_ptr<FrameBuffer>();
    }
    void FrameBufferPool::Add(FrameBuffer* framebuffer)
    {
        m_Pool.push_back(framebuffer);
    }


}
