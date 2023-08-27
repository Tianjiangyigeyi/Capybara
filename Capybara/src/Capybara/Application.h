#pragma once
#ifndef CPBR_PLATFORM_WINDOWS
#define CPBR_PLATFORM_WINDOWS
#endif
#ifndef CPBR_BUILD_DLL
#define CPBR_BUILD_DLL
#endif
#include "Core.h"
namespace Capybara
{
	class CAPYBARA_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};

	Application* CreateApplication();
}
