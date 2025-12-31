project(Capybara LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置静态运行时库
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# 收集所有源文件
# 使用 GLOB_RECURSE 递归查找所有 .cpp 文件
file(GLOB_RECURSE CAPYBARA_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# 收集所有头文件
file(GLOB_RECURSE CAPYBARA_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# 创建静态库或动态库
if(CPBR_BUILD_DLL)
    add_library(Capybara SHARED ${CAPYBARA_SOURCES} ${CAPYBARA_HEADERS})
else()
    add_library(Capybara STATIC ${CAPYBARA_SOURCES} ${CAPYBARA_HEADERS})
endif()

# 确保依赖项在 Capybara 之前构建
add_dependencies(Capybara glfw Glad ImGui)

# 预编译头文件（如果 CMake 版本支持）
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.16")
    target_precompile_headers(Capybara PRIVATE src/precomp.h)
endif()

# 包含目录
target_include_directories(Capybara
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp/include/assimp
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb/include
)

# 链接库
target_link_libraries(Capybara
    PUBLIC
        glfw
        Glad
        ImGui
        opengl32
)

# Windows 特定设置
if(WIN32)
    # 链接 assimp 库（所有配置使用同一个库文件）
    target_link_libraries(Capybara PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp/Debug/assimp-vc140-mt.lib)
    
    target_compile_definitions(Capybara PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# 设置输出名称和目录
set_target_properties(Capybara PROPERTIES
    OUTPUT_NAME "Capybara"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/Capybara"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/Capybara"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/Capybara"
)

