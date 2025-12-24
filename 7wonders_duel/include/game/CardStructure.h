#ifndef CARD_STRUCTURE_H
#define CARD_STRUCTURE_H

#include "../Forward.h"
#include <vector>
#include <string>

class CardSlot {
private:
    Card* card;
    int row;
    int col;
    bool faceDown;
    bool removed;

public:
    CardSlot(Card* card, int row, int col, bool faceDown = false);
    
    bool isAccessible(const std::vector<std::vector<CardSlot*>>& pyramid) const;
    Card* getCard() const { return card; }
    bool isFaceDown() const { return faceDown; }
    bool isRemoved() const { return removed; }
    void remove() { removed = true; card = nullptr; }
    void reveal() { faceDown = false; }
    
    int getRow() const { return row; }
    int getCol() const { return col; }
};

class CardStructure {
private:
    std::vector<std::vector<CardSlot*>> pyramid;
    int totalRows;

public:
    CardStructure();
    ~CardStructure();
    
    void setupPyramid(std::vector<Card*>& cards, int age);
    std::vector<Card*> getAccessibleCards();
    void removeCard(Card* card);
    bool isEmpty() const;
    
    std::string getVisualRepresentation() const;
    
private:
    void clearPyramid();
    void setupAgeIPyramid(std::vector<Card*>& cards);
    void setupAgeIIPyramid(std::vector<Card*>& cards);
    void setupAgeIIIPyramid(std::vector<Card*>& cards);
};

#endif // CARD_STRUCTURE_H
