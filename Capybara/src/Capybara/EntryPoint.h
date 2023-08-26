#pragma once
#include "../Capybara.h"

extern Capybara::Application* Capybara::CreateApplication();

int main(int argc, char **argv)
{
    auto app = Capybara::CreateApplication();
    app->Run();
    delete app;
}