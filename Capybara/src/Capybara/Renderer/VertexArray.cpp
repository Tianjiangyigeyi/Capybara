#include "precomp.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Capybara/Platform/OpenGL/OpenGLVertexArray.h"

namespace Capybara {

    Ref<VertexArray> VertexArray::Create()
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    CPBR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPIType::OpenGL:  return std::make_shared<OpenGLVertexArray>();
        }

        CPBR_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

}