#pragma once

#ifdef CPBR_DEBUG
    #define CPBR_ENABLE_ASSERTS
#endif

#ifdef CPBR_ENABLE_ASSERTS
    #define CPBR_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { CPBR_ERROR("Assertion Failed"); __debugbreak(); } }
    #define CPBR_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { CPBR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

    #define CPBR_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
    #define CPBR_GET_ASSERT_MACRO(...) CPBR_EXPAND_VARGS(CPBR_ASSERT_RESOLVE(__VA_ARGS__, CPBR_ASSERT_MESSAGE, CPBR_ASSERT_NO_MESSAGE))

    #define CPBR_ASSERT(...) CPBR_EXPAND_VARGS( CPBR_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
    #define CPBR_CORE_ASSERT(...) CPBR_EXPAND_VARGS( CPBR_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
    #define CPBR_ASSERT(...)
    #define CPBR_CORE_ASSERT(...)
#endif