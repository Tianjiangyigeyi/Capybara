#include "precomp.h"
#include <Capybara.h>

#include "imgui.h"


class ExampleLayer : public Capybara::Layer
{
public:
	ExampleLayer() : Layer("Example") {}
	void OnUpdate() override
	{
		if (Capybara::Input::IsKeyPressed(CPBR_KEY_TAB))
		{
			CPBR_TRACE("Tab key is pressed!");
		}
	}

	void OnEvent(Capybara::Event& event) override
	{
		// CPBR_TRACE("{0}", event);
	}
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