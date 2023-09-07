#pragma once
#include "Core/Application.h"

#ifdef CPBR_PLATFORM_WINDOWS

extern Capybara::Application* Capybara::CreateApplication();

int main(int argc, char** argv)
{
    Capybara::InitializeCore();
    Capybara::Application* app = Capybara::CreateApplication();
    CPBR_CORE_ASSERT(app, "Client Application is null!");
    app->Run();
    delete app;
    Capybara::ShutdownCore();
}

#endif
