project(ImGui LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置静态运行时库
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# 源文件
set(IMGUI_SOURCES
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
)

# 头文件
set(IMGUI_HEADERS
    imconfig.h
    imgui.h
    imgui_internal.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
)

# 创建静态库
add_library(ImGui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})

# 包含目录
target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Windows 特定设置
if(WIN32)
    target_compile_definitions(ImGui PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

