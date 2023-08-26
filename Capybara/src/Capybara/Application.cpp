#include "Application.h"
#include <iostream>
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
		while (true)
		{
			std::cout << "Application" << std::endl;
		}
	}
}