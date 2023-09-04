#include "precomp.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Capybara
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}
