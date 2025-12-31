@echo off
chcp 65001 >nul 2>&1
setlocal enabledelayedexpansion

REM Build script for Capybara.sln
REM Usage: build.bat [Debug|Release|Dist]

set "CONFIG=%~1"
if "!CONFIG!"=="" set "CONFIG=Debug"

REM Find MSBuild
set "MSBUILD_PATH="

if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" (
    set "MSBUILD_PATH=C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
    goto :found
)
if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe" (
    set "MSBUILD_PATH=C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe"
    goto :found
)
if exist "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe" (
    set "MSBUILD_PATH=C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
    goto :found
)
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" (
    set "MSBUILD_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
    goto :found
)

where msbuild >nul 2>&1
if !ERRORLEVEL! EQU 0 (
    set "MSBUILD_PATH=msbuild"
    goto :found
)

echo Error: Cannot find MSBuild.exe
echo Please install Visual Studio 2022 or 2019 with C++ workload.
exit /b 1

:found
echo Found MSBuild: !MSBUILD_PATH!
echo Building with configuration: !CONFIG!
echo Building CapybaraEditor and dependencies (excluding Sandbox)...

"!MSBUILD_PATH!" Capybara.sln /p:Configuration=!CONFIG! /p:Platform=x64 /m /t:CapybaraEditor

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
