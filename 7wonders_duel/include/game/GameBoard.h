#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "../Forward.h"
#include "MilitaryTrack.h"
#include "CardStructure.h"
#include "ProgressToken.h"
#include <vector>

class GameBoard {
private:
    MilitaryTrack* militaryTrack;
    CardStructure* cardStructure;
    std::vector<ProgressToken*> availableProgressTokens;
    
public:
    GameBoard();
    ~GameBoard();
    
    void initialize();
    void setupAge(int age, std::vector<Card*>& cards);
    
    std::vector<Card*> getAccessibleCards();
    void removeCard(Card* card);
    bool isAgeComplete() const;
    
    MilitaryTrack* getMilitaryTrack() { return militaryTrack; }
    CardStructure* getCardStructure() { return cardStructure; }
    
    // 进度标记管理
    std::vector<ProgressToken*>& getAvailableProgressTokens() { return availableProgressTokens; }
    ProgressToken* takeProgressToken(ProgressType type);
    void removeProgressToken(ProgressToken* token);
    
    std::string getVisualRepresentation() const;
    
private:
    void createProgressTokens();
};

#endif // GAME_BOARD_H
