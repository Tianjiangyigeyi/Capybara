project(Glad LANGUAGES C)

# 设置静态运行时库
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# 源文件
set(GLAD_SOURCES
    src/glad.c
)

# 头文件
set(GLAD_HEADERS
    include/glad/glad.h
    include/KHR/khrplatform.h
)

# 创建静态库
add_library(Glad STATIC ${GLAD_SOURCES} ${GLAD_HEADERS})

# 包含目录
target_include_directories(Glad PUBLIC include)

# Windows 特定设置
if(WIN32)
    target_compile_definitions(Glad PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

