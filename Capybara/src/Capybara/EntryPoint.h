#pragma once
#include "../Capybara.h"
#ifdef CPBR_PLATFORM_WINDOWS
extern Capybara::Application* Capybara::CreateApplication();

int main(int argc, char **argv)
{
    Capybara::Log::Init();
    // Capybara::Log::GetCoreLogger()->warn("Initialized Log!");
    CPBR_CORE_WARN("Initialized Log!");
    // Capybara::Log::GetClientLogger()->info("Hello!");
    int a = 5;
    CPBR_INFO("Hello! Var = {0}", a);

    auto app = Capybara::CreateApplication();
    app->Run();
    delete app;
}

#endif