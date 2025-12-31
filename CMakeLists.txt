cmake_minimum_required(VERSION 3.20)
project(Capybara VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置静态运行时库（必须在添加子目录之前设置）
# 这确保所有子项目（包括 GLFW、GLAD、ImGui）都使用相同的运行时库
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "" FORCE)
endif()

# 设置输出目录（匹配 Premake 的输出结构）
# 注意：对于多配置生成器（如 Visual Studio），输出目录会在每个目标中单独设置
# 这里设置默认值，但每个目标会覆盖它
if(CMAKE_BUILD_TYPE)
    set(OUTPUT_SUFFIX "${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
else()
    # 对于多配置生成器，使用生成器表达式（在目标属性中设置）
    set(OUTPUT_SUFFIX "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 配置选项
option(CPBR_BUILD_DLL "Build Capybara as a DLL" OFF)

# 生成 compile_commands.json 用于 IDE（如 clangd）
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 平台特定设置
if(WIN32)
    add_definitions(-DCPBR_PLATFORM_WINDOWS)
    if(CPBR_BUILD_DLL)
        add_definitions(-DCPBR_BUILD_DLL)
    endif()
endif()

# 构建配置定义（使用生成器表达式以支持多配置生成器）
# 这些定义会在每个目标的编译选项中设置
add_compile_definitions(
    $<$<CONFIG:Debug>:CPBR_DEBUG>
    $<$<CONFIG:Release>:CPBR_RELEASE>
    $<$<CONFIG:Dist>:CPBR_DIST>
)

# 包含目录
set(INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/Capybara/src
    ${CMAKE_SOURCE_DIR}/Capybara/vendor
    ${CMAKE_SOURCE_DIR}/Capybara/vendor/GLFW/include
    ${CMAKE_SOURCE_DIR}/Capybara/vendor/GLAD/include
    ${CMAKE_SOURCE_DIR}/Capybara/vendor/imgui
    ${CMAKE_SOURCE_DIR}/Capybara/vendor/glm
    ${CMAKE_SOURCE_DIR}/Capybara/vendor/assimp/include
    ${CMAKE_SOURCE_DIR}/Capybara/vendor/assimp/include/assimp
    ${CMAKE_SOURCE_DIR}/Capybara/vendor/stb/include
)

# GLFW 配置
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
# 强制 GLFW 使用静态运行时库
set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "" FORCE)

# 添加子目录
add_subdirectory(Capybara/vendor/GLFW)
add_subdirectory(Capybara/vendor/GLAD)
add_subdirectory(Capybara/vendor/imgui)

# 确保 GLFW 使用静态运行时库（必须在 add_subdirectory 之后设置）
if(MSVC AND TARGET glfw)
    set_target_properties(glfw PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
endif()

add_subdirectory(Capybara)
add_subdirectory(CapybaraEditor)

