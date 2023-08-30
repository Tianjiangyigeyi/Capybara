#include "precomp.h"
#include <Capybara.h>
#ifdef CPBR_BUILD_DLL
#undef CPBR_BUILD_DLL
#endif
std::shared_ptr<spdlog::logger> Capybara::Log::s_core_logger_ = nullptr;
std::shared_ptr<spdlog::logger> Capybara::Log::s_client_logger_ = nullptr;

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