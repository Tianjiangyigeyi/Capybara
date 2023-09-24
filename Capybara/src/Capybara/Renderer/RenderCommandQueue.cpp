#include "precomp.h"
#include "RenderCommandQueue.h"
#include "precomp.h"
#include "RenderCommandQueue.h"

#define CPBR_RENDER_TRACE(...) CPBR_CORE_TRACE(__VA_ARGS__)

namespace Capybara {

    RenderCommandQueue::RenderCommandQueue()
    {
        m_CommandBuffer = new unsigned char[10 * 1024 * 1024]; // 10mb buffer
        m_CommandBufferPtr = m_CommandBuffer;
        memset(m_CommandBuffer, 0, 10 * 1024 * 1024);
    }

    RenderCommandQueue::~RenderCommandQueue()
    {
        delete[] m_CommandBuffer;
    }

    // 先是函数指针(8 bytes), 然后是函数体将会用到的大小(8 bytes), 函数体的大小(size)
    void* RenderCommandQueue::Allocate(RenderCommandFn fn, unsigned int size)
    {
        // TODO: alignment
        *reinterpret_cast<RenderCommandFn*>(m_CommandBufferPtr) = fn;
        m_CommandBufferPtr += sizeof(RenderCommandFn);

        *reinterpret_cast<uint32_t*>(m_CommandBufferPtr) = size;
        m_CommandBufferPtr += sizeof(unsigned int);

        void* memory = m_CommandBufferPtr;
        m_CommandBufferPtr += size;

        m_CommandCount++;
        return memory;
    }

    void RenderCommandQueue::Execute()
    {
        //CPBR_RENDER_TRACE("RenderCommandQueue::Execute -- {0} commands, {1} bytes", m_CommandCount, (m_CommandBufferPtr - m_CommandBuffer));

        byte* buffer = m_CommandBuffer;

        for (unsigned int i = 0; i < m_CommandCount; i++)
        {
            RenderCommandFn function = *reinterpret_cast<RenderCommandFn*>(buffer);
            buffer += sizeof(RenderCommandFn);

            unsigned int size = *reinterpret_cast<unsigned int*>(buffer);
            buffer += sizeof(unsigned int);
            function(buffer);
            buffer += size;
        }

        m_CommandBufferPtr = m_CommandBuffer;
        m_CommandCount = 0;
    }

}