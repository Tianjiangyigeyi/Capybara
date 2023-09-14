#include "precomp.h"

#include "Renderer.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Capybara
{

    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            CPBR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        
        CPBR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
