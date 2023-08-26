#pragma once
//#define CPBR_PLATFORM_WINDOWS
//#define CPBR_BUILD_DLL
#include "Core.h"
namespace Capybara
{
	class __declspec(dllexport) Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};

	Application* CreateApplication();
}
