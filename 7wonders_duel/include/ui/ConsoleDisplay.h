#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include "../Forward.h"
#include <string>
#include <vector>

class ConsoleDisplay {
public:
    void displayGameState(GameBoard* board, Player* currentPlayer, Player* opponent);
    void displayPlayerInfo(Player* player, Player* opponent);
    void displayAvailableCards(const std::vector<Card*>& cards);
    void displayFinalScores(Player* p1, Player* p2, GameBoard* board);
    
    void clearScreen();
    void displaySeparator(char c = '=', int length = 50);
};

#endif // CONSOLE_DISPLAY_H
