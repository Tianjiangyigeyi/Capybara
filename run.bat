@echo off
chcp 65001 >nul 2>&1
setlocal enabledelayedexpansion

REM Run script for CapybaraEditor
REM Usage: run.bat [Debug|Release|Dist]

set "CONFIG=%~1"
if "!CONFIG!"=="" set "CONFIG=Debug"

REM Build output directory
set "OUTPUT_DIR=bin\!CONFIG!-windows-x86_64\CapybaraEditor"
set "EXE_PATH=!OUTPUT_DIR!\CapybaraEditor.exe"

REM Check if executable exists
if not exist "!EXE_PATH!" (
    echo Error: Executable not found: !EXE_PATH!
    echo.
    echo Please build the project first using: build.bat !CONFIG!
    echo.
    exit /b 1
)

REM Copy required DLLs to output directory
set "ASSIMP_DLL=Capybara\vendor\assimp\Debug\assimp-vc140-mt.dll"
if exist "!ASSIMP_DLL!" (
    if not exist "!OUTPUT_DIR!\assimp-vc140-mt.dll" (
        echo Copying required DLLs...
        copy /Y "!ASSIMP_DLL!" "!OUTPUT_DIR!\" >nul
    )
)

REM Also check win64 directory
set "ASSIMP_DLL2=Capybara\vendor\assimp\win64\assimp.dll"
if exist "!ASSIMP_DLL2!" (
    if not exist "!OUTPUT_DIR!\assimp.dll" (
        copy /Y "!ASSIMP_DLL2!" "!OUTPUT_DIR!\" >nul
    )
)

echo Running CapybaraEditor (!CONFIG! configuration)...
echo Executable: !EXE_PATH!
echo.

REM Change to CapybaraEditor directory (for assets access)
REM Assets are located in CapybaraEditor/assets/, so we need to run from CapybaraEditor directory
set "SCRIPT_DIR=%~dp0"
set "CAPYBARA_EDITOR_DIR=!SCRIPT_DIR!CapybaraEditor"
set "EXE_FULL_PATH=!SCRIPT_DIR!!EXE_PATH!"

REM Change to CapybaraEditor directory
cd /d "!CAPYBARA_EDITOR_DIR!"

REM Run the executable with full path
"!EXE_FULL_PATH!"

REM Check exit code
if !ERRORLEVEL! NEQ 0 (
    echo.
    echo Program exited with error code: !ERRORLEVEL!
    exit /b !ERRORLEVEL!
)

endlocal

