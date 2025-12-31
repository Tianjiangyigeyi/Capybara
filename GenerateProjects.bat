@echo off
chcp 65001 >nul 2>&1
setlocal enabledelayedexpansion

REM Generate CMake project files
REM This replaces the old Premake-based GenerateProjects.bat

echo Generating CMake project files...
echo.

REM 检查 CMake 是否安装
where cmake >nul 2>&1
if !ERRORLEVEL! NEQ 0 (
    echo Error: CMake is not installed or not in PATH
    echo Please install CMake from https://cmake.org/download/
    exit /b 1
)

REM 设置构建目录
set "BUILD_DIR=build"

REM 运行 CMake 配置
echo Configuring CMake for Visual Studio 2022...
cmake -B "!BUILD_DIR!" -G "Visual Studio 17 2022" -A x64

if !ERRORLEVEL! EQU 0 (
    echo.
    echo CMake configuration succeeded!
    echo Project files generated in: !BUILD_DIR!
    echo.
    echo You can now:
    echo   1. Open Capybara.sln in Visual Studio (if generated)
    echo   2. Or use build.bat to build the project
    exit /b 0
) else (
    echo.
    echo CMake configuration failed with error code: !ERRORLEVEL!
    exit /b !ERRORLEVEL!
)

endlocal
