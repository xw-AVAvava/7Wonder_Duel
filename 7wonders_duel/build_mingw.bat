@echo off
REM 7 Wonders Duel - MinGW Compilation Script
REM Requires MinGW-w64 (g++)

REM Force UTF-8 encoding for console output
chcp 65001 >nul

echo ====================================
echo 7 Wonders Duel - MinGW Build
echo ====================================
echo.

REM Check if g++ is available
where g++ >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Error: g++ compiler not found!
    echo Please install MinGW-w64 and ensure g++ is in your system PATH.
    pause
    exit /b 1
)

REM Create output directories
if not exist bin mkdir bin
if not exist obj mkdir obj
if not exist obj\cards mkdir obj\cards
if not exist obj\game mkdir obj\game
if not exist obj\player mkdir obj\player
if not exist obj\resources mkdir obj\resources
if not exist obj\ui mkdir obj\ui

echo Compiling source files...
echo.

REM Compile all source files
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/Types.cpp -o obj/Types.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/main.cpp -o obj/main.o

g++ -std=c++17 -Wall -Wextra -Iinclude -c src/cards/Card.cpp -o obj/cards/Card.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/cards/AllCards.cpp -o obj/cards/AllCards.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/cards/WonderCard.cpp -o obj/cards/WonderCard.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/cards/CardFactory.cpp -o obj/cards/CardFactory.o

g++ -std=c++17 -Wall -Wextra -Iinclude -c src/game/ProgressToken.cpp -o obj/game/ProgressToken.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/game/MilitaryTrack.cpp -o obj/game/MilitaryTrack.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/game/CardStructure.cpp -o obj/game/CardStructure.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/game/GameBoard.cpp -o obj/game/GameBoard.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/game/VictoryCondition.cpp -o obj/game/VictoryCondition.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/game/Game.cpp -o obj/game/Game.o

g++ -std=c++17 -Wall -Wextra -Iinclude -c src/player/Player.cpp -o obj/player/Player.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/player/PlayerStrategy.cpp -o obj/player/PlayerStrategy.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/player/HumanPlayer.cpp -o obj/player/HumanPlayer.o

g++ -std=c++17 -Wall -Wextra -Iinclude -c src/resources/Cost.cpp -o obj/resources/Cost.o

g++ -std=c++17 -Wall -Wextra -Iinclude -c src/ui/ConsoleDisplay.cpp -o obj/ui/ConsoleDisplay.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/ui/InputHandler.cpp -o obj/ui/InputHandler.o

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Compilation FAILED!
    pause
    exit /b 1
)

echo.
echo Linking objects...
echo.

REM Link all object files
g++ -std=c++17 -o bin/7wonders_duel.exe ^
    obj/Types.o ^
    obj/main.o ^
    obj/cards/Card.o ^
    obj/cards/AllCards.o ^
    obj/cards/WonderCard.o ^
    obj/cards/CardFactory.o ^
    obj/game/ProgressToken.o ^
    obj/game/MilitaryTrack.o ^
    obj/game/CardStructure.o ^
    obj/game/GameBoard.o ^
    obj/game/VictoryCondition.o ^
    obj/game/Game.o ^
    obj/player/Player.o ^
    obj/player/PlayerStrategy.o ^
    obj/player/HumanPlayer.o ^
    obj/resources/Cost.o ^
    obj/ui/ConsoleDisplay.o ^
    obj/ui/InputHandler.o

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Linking FAILED!
    pause
    exit /b 1
)

echo.
echo ====================================
echo Build SUCCESSFUL!
echo ====================================
echo.
echo Executable: bin\7wonders_duel.exe
echo.
echo To run the game, double-click run_game.bat
echo.
pause
