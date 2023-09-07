#pragma once

namespace Capybara
{
    void InitializeCore();
    void ShutdownCore();

    
}

#ifdef CPBR_PLATFORM_WINDOWS
#if CPBR_DYNAMIC_LINK
    #ifdef CPBR_BUILD_DLL
        #define CAPYBARA_API __declspec(dllexport)
    #else
        #define CAPYBARA_API __declspec(dllimport)
    #endif
#else
    #define CAPYBARA_API
#endif

#else
    #error Capybara only supports windows
#endif

#ifdef CPBR_DEBUG
    #define CPBR_ENABLE_ASSERTS
#endif

#ifdef CPBR_ENABLE_ASSERTS
    #define CPBR_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { CPBR_ERROR("Assertion Failed!"); __debugbreak(); } }
    #define CPBR_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { CPBR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

    #define CPBR_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro

    #define CPBR_ASSERT(...) CPBR_ASSERT_RESOLVE(__VA_ARGS__, CPBR_ASSERT_MESSAGE, CPBR_ASSERT_NO_MESSAGE)(__VA_ARGS__)
    #define CPBR_CORE_ASSERT(...) CPBR_ASSERT_RESOLVE(__VA_ARGS__, CPBR_ASSERT_MESSAGE, CPBR_ASSERT_NO_MESSAGE)(__VA_ARGS__)
#else
    #define CPBR_ASSERT(...)
    #define CPBR_CORE_ASSERT(...) 
#endif

#define BIT(x) 1 << x
#define CPBR_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Capybara
{
    template <typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

    using byte = unsigned char;
}
