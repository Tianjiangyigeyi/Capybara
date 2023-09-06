#include "precomp.h"
#include <Capybara.h>

#include "imgui.h"
#include "glm/gtx/transform.hpp"


class ExampleLayer : public Capybara::Layer
{
public:
	ExampleLayer() : Layer("Example"),
	m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
	m_CameraPosition(0.0f)
	{
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		float vertices2[4 * 3] = {
			-0.5f, -0.5f, 0.0f, 
			 0.5f, -0.5f, 0.0f, 
			 0.5f,  0.5f, 0.0f,
			 -0.5f,  0.5f, 0.0f
		};
		unsigned int indices[3] = { 0, 1, 2 };
		unsigned int indices2[6] = { 0, 1, 2, 2, 3, 0};

		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;			
			uniform mat4 u_Transform;			

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		std::string fragmenSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;

			in vec3 v_Position; 
			in vec4 v_Color;
			void main()
			{
				//color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		std::string vertexSrc2 = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;			
			uniform mat4 u_Transform;			

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		std::string fragmenSrc2 = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position; 
			uniform vec4 u_Color;
			void main()
			{
				color = u_Color;
			}
		)";

		std::shared_ptr<Capybara::VertexBuffer> squareVB;
		std::shared_ptr<Capybara::IndexBuffer> squareIB;
		std::shared_ptr<Capybara::VertexBuffer> vertexBuffer;
		std::shared_ptr<Capybara::IndexBuffer> indexBuffer;
		
		m_VertexArray.reset(Capybara::VertexArray::Create());
		m_SquareVA.reset(Capybara::VertexArray::Create());

		indexBuffer.reset(Capybara::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexBuffer.reset(Capybara::VertexBuffer::Create(vertices, sizeof(vertices)));
		squareVB.reset(Capybara::VertexBuffer::Create(vertices2, sizeof(vertices2)));
		squareIB.reset(Capybara::IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));

		m_Shader.reset(new Capybara::Shader(vertexSrc, fragmenSrc));
		m_SquareShader.reset(new Capybara::Shader(vertexSrc2, fragmenSrc2));

		
		vertexBuffer->SetLayout({
	        { Capybara::ShaderDataType::Float3, "a_Position" },
	        { Capybara::ShaderDataType::Float4, "a_Color" }
		});
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);
		
		squareVB->SetLayout({
			{ Capybara::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);
		m_SquareVA->SetIndexBuffer(squareIB);
		
	}
	void OnUpdate(Capybara::Timestep ts) override
	{
		if (Capybara::Input::IsKeyPressed(CPBR_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraSpeed * ts;
		}
		if (Capybara::Input::IsKeyPressed(CPBR_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraSpeed * ts;
		}
		if (Capybara::Input::IsKeyPressed(CPBR_KEY_UP))
		{
			m_CameraPosition.y += m_CameraSpeed * ts;
		}
		if (Capybara::Input::IsKeyPressed(CPBR_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraSpeed * ts;
		}
		
		if (Capybara::Input::IsKeyPressed(CPBR_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		if (Capybara::Input::IsKeyPressed(CPBR_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		if (Capybara::Input::IsKeyPressed(CPBR_KEY_SPACE))
		{
			m_CameraPosition.x = m_CameraPosition.y = 0.0f;
		}


		Capybara::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
		Capybara::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
			
		Capybara::Renderer::BeginScene(m_Camera);
		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		
		
		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				// Just a Test
				if (i % 2 == 0)
				{
					m_SquareShader->UploadUniformFloat4("u_Color", redColor);
				}
				else
				{
					m_SquareShader->UploadUniformFloat4("u_Color", blueColor);
				}
				Capybara::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
			}
			
		}
		Capybara::Renderer::Submit(m_Shader, m_VertexArray);

		Capybara::Renderer::EndScene();
			
	}
	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Capybara::Event& event) override
	{
	}

private:
	std::shared_ptr<Capybara::Shader> m_Shader;
	std::shared_ptr<Capybara::Shader> m_SquareShader;

	std::shared_ptr<Capybara::VertexArray> m_VertexArray;
	std::shared_ptr<Capybara::VertexArray> m_SquareVA;
		
	Capybara::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 100.0f;
};

class SandBox : public Capybara::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}
	~SandBox()
	{
	}
};

Capybara::Application* Capybara::CreateApplication()
{
	return new SandBox();
}