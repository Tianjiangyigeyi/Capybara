#pragma once


#include "Core.h"

#include "Window.h"
#include "Capybara/LayerStack.h"
#include "Capybara/Events/Event.h"
#include "Capybara/Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "Capybara/Renderer/Shader.h"
#include "Capybara/Renderer/Buffer.h"

namespace Capybara
{
	class CAPYBARA_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
		void OnEvent(Event& event);
	
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() {return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent &event);
		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray; 
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		
		static Application* s_Instance;
	};

	
	// To be defined in CLIENT
	Application* CreateApplication();
}
