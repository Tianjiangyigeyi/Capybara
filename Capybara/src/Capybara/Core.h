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

#define BIT(x) 1 << x