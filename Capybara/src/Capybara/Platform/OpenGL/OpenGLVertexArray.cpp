#include "precomp.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

#include "Capybara/Renderer/Renderer.h"

namespace Capybara {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Capybara::ShaderDataType::Float:    return GL_FLOAT;
			case Capybara::ShaderDataType::Float2:   return GL_FLOAT;
			case Capybara::ShaderDataType::Float3:   return GL_FLOAT;
			case Capybara::ShaderDataType::Float4:   return GL_FLOAT;
			case Capybara::ShaderDataType::Mat3:     return GL_FLOAT;
			case Capybara::ShaderDataType::Mat4:     return GL_FLOAT;
			case Capybara::ShaderDataType::Int:      return GL_INT;
			case Capybara::ShaderDataType::Int2:     return GL_INT;
			case Capybara::ShaderDataType::Int3:     return GL_INT;
			case Capybara::ShaderDataType::Int4:     return GL_INT;
			case Capybara::ShaderDataType::Bool:     return GL_BOOL;
		}

		CPBR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		Renderer::Submit([this]() {
			glGenVertexArrays(1, &m_RendererID);
		});
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		Renderer::Submit([this]() {
			glDeleteVertexArrays(1, &m_RendererID);
		});
	}

	void OpenGLVertexArray::Bind() const
	{
		Renderer::Submit([this]() {
			glBindVertexArray(m_RendererID);
		});
	}

	void OpenGLVertexArray::Unbind() const
	{
		Renderer::Submit([this]() {
			glBindVertexArray(0);
		});
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		CPBR_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		Bind();
		vertexBuffer->Bind();

		Renderer::Submit([this, vertexBuffer]() {
			const auto& layout = vertexBuffer->GetLayout();
			for (const auto& element : layout)
			{
				auto glBaseType = ShaderDataTypeToOpenGLBaseType(element.Type);
				glEnableVertexAttribArray(m_VertexBufferIndex);
				if (glBaseType == GL_INT)
				{
					glVertexAttribIPointer(m_VertexBufferIndex,
						element.GetComponentCount(),
						glBaseType,
						layout.GetStride(),
						(const void*)(intptr_t)element.Offset);
				}
				else
				{
					glVertexAttribPointer(m_VertexBufferIndex,
						element.GetComponentCount(),
						glBaseType,
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(intptr_t)element.Offset);
				}
				m_VertexBufferIndex++;
			}
		});
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		Bind();
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
