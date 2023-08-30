#include "precomp.h"
#include "Log.h"

std::shared_ptr<spdlog::logger> Capybara::Log::s_core_logger_ = nullptr;
std::shared_ptr<spdlog::logger> Capybara::Log::s_client_logger_ = nullptr;