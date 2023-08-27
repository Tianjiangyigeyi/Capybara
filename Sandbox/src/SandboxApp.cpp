
#include <Capybara.h>
#ifdef CPBR_BUILD_DLL
#undef CPBR_BUILD_DLL
#endif

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