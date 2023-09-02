#include "precomp.h"
#include "Application.h"

#include <glad/glad.h>

#include "Input.h"

namespace Capybara
{
#define BIND_EVENT_FN(x) [this](auto&&... args) -> decltype(auto) { return this->x(std::forward<decltype(args)>(args)...); }
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		CPBR_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();

	}

	
	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		CPBR_CORE_TRACE("{0}", event);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.m_Handled)
			{
				break;
			}
		}
	}
	void Application::Run() 
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (auto layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			
			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent &event)
	{
		m_Running = false;
		return true;
	}
}