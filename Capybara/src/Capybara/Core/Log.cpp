#include "precomp.h"
#include "Log.h"

std::shared_ptr<spdlog::logger> Capybara::Log::s_CoreLogger = nullptr;
std::shared_ptr<spdlog::logger> Capybara::Log::s_ClientLogger = nullptr;