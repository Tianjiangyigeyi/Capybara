project(CapybaraEditor LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置静态运行时库
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# 源文件列表
set(EDITOR_SOURCES
    src/CapybaraEditor.cpp
    src/EditorLayer.cpp
)

set(EDITOR_HEADERS
    src/EditorLayer.h
)

# 创建可执行文件
add_executable(CapybaraEditor ${EDITOR_SOURCES} ${EDITOR_HEADERS})

# 包含目录
target_include_directories(CapybaraEditor
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/Capybara/src
        ${CMAKE_SOURCE_DIR}/Capybara/vendor
        ${CMAKE_SOURCE_DIR}/Capybara/vendor/glm
)

# 链接库
target_link_libraries(CapybaraEditor
    PRIVATE
        Capybara
)

# Windows 特定设置
if(WIN32)
    # 链接 assimp 库（所有配置使用同一个库文件）
    target_link_libraries(CapybaraEditor PRIVATE ${CMAKE_SOURCE_DIR}/Capybara/vendor/assimp/Debug/assimp-vc140-mt.lib)
    
    target_compile_definitions(CapybaraEditor PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# 设置输出名称和目录
set_target_properties(CapybaraEditor PROPERTIES
    OUTPUT_NAME "CapybaraEditor"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/CapybaraEditor"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/CapybaraEditor"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/CapybaraEditor"
)

