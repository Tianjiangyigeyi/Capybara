#include "precomp.h"
#include <Capybara.h>
#include <Capybara/EntryPoint.h>

#include "EditorLayer.h"

class CapybaraEditorApplication : public Capybara::Application
{
public:
	CapybaraEditorApplication(const Capybara::ApplicationProps& props)
		: Application(props)
	{
	}

	virtual void OnInit() override
	{
		PushLayer(new Capybara::EditorLayer());
	}
};

Capybara::Application* Capybara::CreateApplication()
{
	return new CapybaraEditorApplication({"CapybaraEditor", 1600, 900});
}