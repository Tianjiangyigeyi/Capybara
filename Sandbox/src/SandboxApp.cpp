#include <Capybara.h>
class SandBox : public Capybara::Application
{
public:
	SandBox()
	{
	}
	~SandBox()
	{
	}
};

Capybara::Application* Capybara::CreateApplication()
{
	return new SandBox();
}