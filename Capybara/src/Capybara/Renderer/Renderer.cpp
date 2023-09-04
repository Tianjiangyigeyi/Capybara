#include "precomp.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Capybara
{

    // TODO: include camera, lights, environment
    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}
