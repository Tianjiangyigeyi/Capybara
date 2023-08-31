#include "precomp.h"
#include <Capybara.h>


class ExampleLayer : public Capybara::Layer
{
public:
	ExampleLayer() : Layer("Example") {}
	void OnUpdate() override
	{
		CPBR_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(Capybara::Event& event) override
	{
		CPBR_TRACE("{0}", event);
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