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

int main()
{
	SandBox* sandbox = new SandBox();
	sandbox->Run();
	delete sandbox;
	return 0;
}