#pragma once

#include "Capybara/Renderer/RendererAPI.h"

namespace Capybara
{
    enum class FrameBufferFormat
    {
        None = 0,
        RGBA8 = 1,
        RGBA16F = 2
    };
    
    class FrameBuffer
    {
    public:
        static FrameBuffer* Create(uint32_t width, uint32_t height, FrameBufferFormat format);

        virtual ~FrameBuffer() {}
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual void BindTexture(uint32_t slot = 0) const = 0;

        virtual RendererID GetRendererID() const = 0;
        virtual RendererID GetColorAttachmentRendererID() const = 0;
        virtual RendererID GetDepthAttachmentRendererID() const = 0;
    };

    class FrameBufferPool final
    {
    public:
        FrameBufferPool(uint32_t maxFBs = 32);
        ~FrameBufferPool();

        std::weak_ptr<FrameBuffer> AllocateBuffer();
        void Add(FrameBuffer* framebuffer);

        const std::vector<FrameBuffer*>& GetAll() const { return m_Pool; }

        inline static FrameBufferPool* GetGlobal() { return s_Instance; }

    private:
        std::vector<FrameBuffer*> m_Pool;
        static FrameBufferPool* s_Instance;
    };


}
