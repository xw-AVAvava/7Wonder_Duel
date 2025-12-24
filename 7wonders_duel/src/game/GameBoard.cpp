#include "../../include/game/GameBoard.h"
#include <algorithm>
#include <sstream>

GameBoard::GameBoard() {
    militaryTrack = new MilitaryTrack();
    cardStructure = new CardStructure();
}

GameBoard::~GameBoard() {
    delete militaryTrack;
    delete cardStructure;
    
    for (auto* token : availableProgressTokens) {
        delete token;
    }
}

void GameBoard::initialize() {
    militaryTrack->initialize();
    createProgressTokens();
}

void GameBoard::createProgressTokens() {
    availableProgressTokens.clear();
    
    availableProgressTokens.push_back(new ProgressToken(ProgressType::AGRICULTURE, "农业"));
    availableProgressTokens.push_back(new ProgressToken(ProgressType::ARCHITECTURE, "建筑学"));
    availableProgressTokens.push_back(new ProgressToken(ProgressType::ECONOMY, "经济"));
    availableProgressTokens.push_back(new ProgressToken(ProgressType::LAW, "法律"));
    availableProgressTokens.push_back(new ProgressToken(ProgressType::MASONRY, "石工术"));
    availableProgressTokens.push_back(new ProgressToken(ProgressType::MATHEMATICS, "数学"));
    availableProgressTokens.push_back(new ProgressToken(ProgressType::PHILOSOPHY, "哲学"));
    availableProgressTokens.push_back(new ProgressToken(ProgressType::STRATEGY, "策略"));
    availableProgressTokens.push_back(new ProgressToken(ProgressType::THEOLOGY, "神学"));
    availableProgressTokens.push_back(new ProgressToken(ProgressType::URBANISM, "城市规划"));
}

void GameBoard::setupAge(int age, std::vector<Card*>& cards) {
    cardStructure->setupPyramid(cards, age);
}

std::vector<Card*> GameBoard::getAccessibleCards() {
    return cardStructure->getAccessibleCards();
}

void GameBoard::removeCard(Card* card) {
    cardStructure->removeCard(card);
}

bool GameBoard::isAgeComplete() const {
    return cardStructure->isEmpty();
}

ProgressToken* GameBoard::takeProgressToken(ProgressType type) {
    for (auto it = availableProgressTokens.begin(); it != availableProgressTokens.end(); ++it) {
        if ((*it)->getType() == type) {
            ProgressToken* token = *it;
            availableProgressTokens.erase(it);
            return token;
        }
    }
    return nullptr;
}

void GameBoard::removeProgressToken(ProgressToken* token) {
    auto it = std::find(availableProgressTokens.begin(), availableProgressTokens.end(), token);
    if (it != availableProgressTokens.end()) {
        availableProgressTokens.erase(it);
    }
}

std::string GameBoard::getVisualRepresentation() const {
    std::stringstream ss;
    
    ss << militaryTrack->getVisualRepresentation();
    ss << "\n";
    ss << cardStructure->getVisualRepresentation();
    ss << "\n可用进度标记: " << availableProgressTokens.size() << "个\n";
    
    return ss.str();
}
