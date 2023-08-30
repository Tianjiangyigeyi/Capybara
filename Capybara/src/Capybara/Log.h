#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
namespace Capybara
{
    class CAPYBARA_API Log
    {
    public:
        static void Init()
        {
            spdlog::set_pattern("%^[%T] %n: %v%$");
        
            s_core_logger_ = spdlog::stdout_color_mt("CAPYBARA");
            s_core_logger_->set_level(spdlog::level::trace);

            s_client_logger_ = spdlog::stdout_color_mt("APP");
            s_client_logger_->set_level(spdlog::level::trace);
        }

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
        {
            while (s_core_logger_ == nullptr)
            {
                Init();
            }
            return s_core_logger_;
        }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
        { 
            while (s_client_logger_ == nullptr)
            {
                Init();
            }
            return s_client_logger_;
        }
    private:
        static std::shared_ptr<spdlog::logger> s_core_logger_;
        static std::shared_ptr<spdlog::logger> s_client_logger_;
    };
    
}

// Core log Macros
#define CPBR_CORE_ERROR(...)        ::Capybara::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CPBR_CORE_INFO(...)         ::Capybara::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CPBR_CORE_WARN(...)         ::Capybara::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CPBR_CORE_TRACE(...)        ::Capybara::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CPBR_CORE_FATAL(...)        ::Capybara::Log::GetCoreLogger()->fatal(__VA_ARGS__)


// Client log Macros
#define CPBR_ERROR(...)         ::Capybara::Log::GetClientLogger()->error(__VA_ARGS__)
#define CPBR_INFO(...)          ::Capybara::Log::GetClientLogger()->info(__VA_ARGS__)
#define CPBR_WARN(...)          ::Capybara::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CPBR_TRACE(...)         ::Capybara::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CPBR_FATAL(...)         ::Capybara::Log::GetClientLogger()->fatal(__VA_ARGS__)
