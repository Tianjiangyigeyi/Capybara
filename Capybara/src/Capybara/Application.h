#pragma once


#ifndef CPBR_PLATFORM_WINDOWS
#define CPBR_PLATFORM_WINDOWS
#endif
#ifndef CPBR_BUILD_DLL
#define CPBR_BUILD_DLL
#endif



#include "Core.h"
#include "Events/Event.h"
#include "Capybara/Events/ApplicationEvent.h"
#include "Window.h"
namespace Capybara
{
	class CAPYBARA_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
		void OnEvent(Event& event);
	private:
		bool OnWindowClose(WindowCloseEvent &event);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	
	// To be defined in CLIENT
	Application* CreateApplication();
}
