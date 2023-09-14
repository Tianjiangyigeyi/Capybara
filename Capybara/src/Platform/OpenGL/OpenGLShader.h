#pragma once
#include "Capybara/Renderer/Shader.h"
namespace Capybara
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);

        void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
        void UploadUniformFloat(const std::string& name, float value);

        void UploadUniformInt(const std::string& name, int value);
    private:
        uint32_t m_RendererID;
    };
}
