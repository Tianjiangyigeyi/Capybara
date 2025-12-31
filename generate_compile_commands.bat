@echo off
chcp 65001 >nul 2>&1
echo 正在生成 compile_commands.json 文件...
echo.

REM 检查是否安装了 Ninja
where ninja >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo 使用 Ninja 生成器...
    if not exist "build-ninja" (
        cmake -B build-ninja -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    )
    cmake --build build-ninja
    if exist "build-ninja\compile_commands.json" (
        copy /Y "build-ninja\compile_commands.json" "build\compile_commands.json"
        echo 成功生成 compile_commands.json！
    ) else (
        echo 警告: 未能生成 compile_commands.json
    )
) else (
    echo 未找到 Ninja，尝试使用 Visual Studio 生成器...
    echo 注意: Visual Studio 生成器可能无法生成 compile_commands.json
    echo 建议安装 Ninja: https://ninja-build.org/
    echo.
    echo 或者手动运行:
    echo   cmake -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    echo   cmake --build build --config Debug
)

pause

