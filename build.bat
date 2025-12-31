@echo off
chcp 65001 >nul 2>&1
setlocal enabledelayedexpansion

REM Build script for Capybara using CMake
REM Usage: build.bat [Debug|Release|Dist]

set "CONFIG=%~1"
if "!CONFIG!"=="" set "CONFIG=Debug"

REM 检查 CMake 是否安装
where cmake >nul 2>&1
if !ERRORLEVEL! NEQ 0 (
    echo Error: CMake is not installed or not in PATH
    echo Please install CMake from https://cmake.org/download/
    exit /b 1
)

echo Found CMake: 
cmake --version
echo.
echo Building with configuration: !CONFIG!
echo.

REM 设置构建目录
set "BUILD_DIR=build"
set "CMAKE_BUILD_TYPE=!CONFIG!"

REM 如果是第一次构建，运行 CMake 配置
REM 对于 Visual Studio 生成器，不需要指定 CMAKE_BUILD_TYPE
if not exist "!BUILD_DIR!" (
    echo Configuring CMake...
    cmake -B "!BUILD_DIR!" -G "Visual Studio 17 2022" -A x64
    if !ERRORLEVEL! NEQ 0 (
        echo CMake configuration failed!
        exit /b !ERRORLEVEL!
    )
    echo.
)

REM 构建项目
echo Building CapybaraEditor and dependencies...
cmake --build "!BUILD_DIR!" --config !CONFIG! --target CapybaraEditor -j

if !ERRORLEVEL! EQU 0 (
    echo.
    echo Build succeeded!
    exit /b 0
) else (
    echo.
    echo Build failed with error code: !ERRORLEVEL!
    exit /b !ERRORLEVEL!
)

endlocal
