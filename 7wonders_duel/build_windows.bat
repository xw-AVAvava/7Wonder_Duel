@echo off
REM 7 Wonders Duel - Windows Compilation Script (CMake)
REM Requires CMake and Visual Studio or MinGW

REM Force UTF-8 encoding for console output
chcp 65001 >nul

echo ====================================
echo 7 Wonders Duel - Windows Build (CMake)
echo ====================================
echo.

REM Check for build directory and clean if exists
if exist build (
    echo Cleaning old build directory...
    rmdir /s /q build
)

REM Create build directory
echo Creating build directory...
mkdir build
cd build

echo.
echo Configuring project with CMake...
echo.

REM Configure project
cmake ..

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Configuration FAILED! Please ensure CMake and a C++ compiler are installed.
    echo.
    pause
    exit /b 1
)

echo.
echo Building project...
echo.

REM Build project
cmake --build . --config Release

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Build FAILED!
    pause
    exit /b 1
)

echo.
echo ====================================
echo Build SUCCESSFUL!
echo ====================================
echo.
echo Executable location: build\bin\Release\7wonders_duel.exe
echo.
echo To run the game, double-click run_game.bat
echo.
pause
