#pragma once


#include "Capybara/Core/Base.h"
#include "Capybara/Core/TimeStep.h"
#include "Capybara/Core/Window.h"
#include "Capybara/Core/LayerStack.h"

#include "Capybara/Core/Events/ApplicationEvent.h"

#include "Capybara/ImGui/ImGuiLayer.h"


namespace Capybara
{
	struct ApplicationProps
	{
		std::string Name;
		uint32_t WindowWidth, WindowHeight;
	};
	
	class Application
	{
	public:
		Application(const ApplicationProps& props = { "Capybara Engine", 1280, 720 });
		virtual ~Application();
		
		void Run();

		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate(TimeStep ts) {}
		
		virtual void OnEvent(Event& event);
	
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void RenderImGui();

		std::string OpenFile(const std::string& filter) const;

		inline static Application& Get() {return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		float GetTime() const;
	private:
		bool OnWindowClose(WindowCloseEvent &event);
		bool OnWindowResize(WindowResizeEvent &event);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true, m_Minimized = false;
		LayerStack m_LayerStack;
		TimeStep m_TimeStep;
		
		float m_LastFrameTime = 0.0f;
		static Application* s_Instance;
	};
	
	// To be defined in CLIENT
	Application* CreateApplication();
}
