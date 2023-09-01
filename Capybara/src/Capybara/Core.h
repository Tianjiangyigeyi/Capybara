#pragma once

// 应该是在预处理器设置里define CPBR_PLATFORM_WINDOWS或CPBR_BUILD_DLL
// 目的是简化app和engine的export/import操作
#ifdef CPBR_PLATFORM_WINDOWS
    #ifdef CPBR_BUILD_DLL
        #define CAPYBARA_API __declspec(dllexport)
    #else
        #define CAPYBARA_API __declspec(dllimport)
    #endif
#else
    #error Capybara only supports windows
#endif

#ifdef CPBR_DEGUG
    #define CPBR_ENABLE_ASSERTS
#endif

#ifdef CPBR_ENABLE_ASSERTS
    #define CPBR_ASSERT(x, ...) { if (!(x)) {CPBR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define CPBR_CORE_ASSERT(x, ...) { if (!(x)) {CPBR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define CPBR_ASSERT(x, ...)
    #define CPBR_CORE_ASSERT(x, ...) 
#endif

#define BIT(x) 1 << x
#define CPBR_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
