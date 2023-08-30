#include "precomp.h"
#include "Application.h"

#include "Capybara/Events/ApplicationEvent.h"
#include "Capybara/Log.h"
namespace Capybara
{
	
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 700);
		if (e.IsInCategory(EventCategoryApplication))
		{
			CPBR_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			CPBR_TRACE(e);
		} 
		while (true)
		{
		}
	}
}