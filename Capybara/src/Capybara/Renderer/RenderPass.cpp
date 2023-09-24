#include "precomp.h"
#include "RenderPass.h"

#include "Renderer.h"

#include "Capybara/Platform/OpenGL/OpenGLRenderPass.h"

namespace Capybara {

    Ref<RenderPass> RenderPass::Create(const RenderPassSpecification& spec)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None:    CPBR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        // case RendererAPIType::OpenGL:  return std::make_shared<OpenGLRenderPass>(spec);
        case RendererAPIType::OpenGL:  return CreateRef<OpenGLRenderPass>(spec);
        }

        CPBR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}