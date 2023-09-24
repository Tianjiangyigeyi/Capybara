#include "precomp.h"
#include "Shader.h"

#include "Capybara/Renderer/Renderer.h"
#include "Capybara/Platform/OpenGL/OpenGLShader.h"

namespace Capybara {

	std::vector<Ref<Shader>> Shader::s_AllShaders;

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		Ref<Shader> result = nullptr;

		switch (RendererAPI::Current())
		{
		case RendererAPIType::None: return nullptr;
		case RendererAPIType::OpenGL: result = CreateRef<OpenGLShader>(filepath);
		}
		s_AllShaders.push_back(result);
		return result;
	}

	Ref<Shader> Shader::CreateFromString(const std::string& source)
	{
		Ref<Shader> result = nullptr;

		switch (RendererAPI::Current())
		{
		case RendererAPIType::None: return nullptr;
		case RendererAPIType::OpenGL: result = OpenGLShader::CreateFromString(source);
		}
		s_AllShaders.push_back(result);
		return result;
	}

	ShaderLibrary::ShaderLibrary()
	{
	}

	ShaderLibrary::~ShaderLibrary()
	{
	}

	void ShaderLibrary::Add(const Capybara::Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		CPBR_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end());
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Load(const std::string& path)
	{
		auto shader = Ref<Shader>(Shader::Create(path));
		auto& name = shader->GetName();
		CPBR_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end());
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Load(const std::string& name, const std::string& path)
	{
		CPBR_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end());
		m_Shaders[name] = Ref<Shader>(Shader::Create(path));
	}

	Ref<Shader>& ShaderLibrary::Get(const std::string& name)
	{
		CPBR_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end());
		return m_Shaders[name];
	}

}