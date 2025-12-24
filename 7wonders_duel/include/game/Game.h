#ifndef GAME_H
#define GAME_H

#include "../Forward.h"
#include "../Types.h"
#include "GameBoard.h"
#include "VictoryCondition.h"
#include <vector>

class Game {
private:
    GameBoard* board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    int currentAge;
    VictoryCondition* victoryChecker;
    std::vector<Card*> discardPile;
    std::vector<Card*> allCards;  // 用于内存管理
    std::vector<WonderCard*> allWonders;  // 用于内存管理
    
    bool gameOver;
    Player* winner;
    VictoryType victoryType;
    
    ConsoleDisplay* display;
    InputHandler* inputHandler;

public:
    Game();
    ~Game();
    
    void initialize();
    void setupPlayers();
    void setupWonders();
    void startGame();
    
    void playAge(int age);
    void playTurn();
    bool executeAction(Action* action, Player* player);
    
    void checkAndHandleVictory();
    bool checkVictory();
    void switchPlayer();
    void endGame();
    
    void updateMilitaryTrack(int militaryPowerChange);
    void checkProgressTokens(Player* player);
    
    GameBoard* getBoard() { return board; }
    Player* getCurrentPlayer() { return currentPlayer; }
    Player* getOpponent();
    std::vector<Card*>& getDiscardPile() { return discardPile; }
    
private:
    void cleanupCards();
};

#endif // GAME_H
