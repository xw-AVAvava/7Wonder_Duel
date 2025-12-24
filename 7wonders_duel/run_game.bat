@echo off
REM 7 Wonders Duel - Run Script

REM Force UTF-8 encoding for console output
chcp 65001 >nul

echo ====================================
echo 7 Wonders Duel - Starting Game
echo ====================================
echo.

REM Check for executable in bin (MinGW build)
if exist bin\7wonders_duel.exe (
    echo Found executable in bin\. Running...
    cd bin
    7wonders_duel.exe
    cd ..
    goto :END
)

REM Check for executable in build\bin\Release (CMake/VS build)
if exist build\bin\Release\7wonders_duel.exe (
    echo Found executable in build\bin\Release\. Running...
    cd build\bin\Release
    7wonders_duel.exe
    cd ..\..\..
    goto :END
)

REM Check for executable in build\bin (Alternative CMake build)
if exist build\bin\7wonders_duel.exe (
    echo Found executable in build\bin\. Running...
    cd build\bin
    7wonders_duel.exe
    cd ..\..
    goto :END
)

echo Error: Game executable not found!
echo.
echo Please compile the project first:
echo   - Using CMake: build_windows.bat
echo   - Using MinGW: build_mingw.bat
echo.
pause
exit /b 1

:END
pause
