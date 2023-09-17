#include "precomp.h"

#include "Renderer.h"

#include "Capybara/Platform/OpenGL/OpenGLBuffer.h"

namespace Capybara {

    Ref<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size, VertexBufferUsage usage)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    return nullptr;
        case RendererAPIType::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(data, size, usage);
        }
        CPBR_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size, VertexBufferUsage usage)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    return nullptr;
        case RendererAPIType::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(size, usage);
        }
        CPBR_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
	
    Ref<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    return nullptr;
        case RendererAPIType::OpenGL:  return std::make_shared<OpenGLIndexBuffer>(data, size);
        }
        CPBR_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;

    }
}