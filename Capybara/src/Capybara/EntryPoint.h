#pragma once
#include "../Capybara.h"
#ifdef CPBR_PLATFORM_WINDOWS

extern Capybara::Application* Capybara::CreateApplication();

int main(int argc, char **argv)
{
    Capybara::Log::Init();
    CPBR_CORE_INFO("Initialized Log!");

    auto app = Capybara::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif