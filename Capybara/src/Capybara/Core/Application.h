﻿#pragma once

#include "Capybara/Core/Base.h"
#include "Capybara/Core/Timestep.h"
#include "Capybara/Core/Window.h"
#include "Capybara/Core/LayerStack.h"

#include "Capybara/Core/Events/ApplicationEvent.h"

#include "Capybara/ImGui/ImGuiLayer.h"

namespace Capybara {

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
		void PushOverlay(Layer* layer);
		void RenderImGui();

		std::string OpenFile(const std::string& filter) const;

		inline Window& GetWindow() { return *m_Window; }
		
		static inline Application& Get() { return *s_Instance; }

		float GetTime() const; // TODO: This should be in "Platform"
		private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		Scope<Window> m_Window;
		bool m_Running = true, m_Minimized = false;
		LayerStack m_LayerStack;
		TimeStep m_TimeStep;
		ImGuiLayer* m_ImGuiLayer;

		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	// Implemented by CLIENT
	Application* CreateApplication();
}