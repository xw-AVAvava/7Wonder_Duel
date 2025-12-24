#include "../../include/ui/InputHandler.h"
#include "../../include/player/Player.h"
#include "../../include/cards/Card.h"
#include "../../include/cards/WonderCard.h"
#include "../../include/game/GameBoard.h"
#include <iostream>
#include <sstream>
#include <limits>

int InputHandler::getIntInput(const std::string& prompt, int min, int max) {
    int value;
    std::string input;
    
    while (true) {
        if (!prompt.empty()) {
            std::cout << prompt << " (" << min << "-" << max << "): ";
        }
        
        std::getline(std::cin, input);
        
        if (validateInput(input, value, min, max)) {
            return value;
        }
        
        std::cout << "无效输入,请输入 " << min << " 到 " << max << " 之间的数字。" << std::endl;
    }
}

std::string InputHandler::getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt << ": ";
    std::getline(std::cin, input);
    return input;
}

bool InputHandler::validateInput(const std::string& input, int& value, int min, int max) {
    std::stringstream ss(input);
    if (!(ss >> value)) {
        return false;
    }
    
    // 检查是否还有其他字符
    std::string remaining;
    ss >> remaining;
    if (!remaining.empty()) {
        return false;
    }
    
    return value >= min && value <= max;
}

Action* InputHandler::getPlayerAction(Player* player, Player* opponent,
                                     const std::vector<Card*>& availableCards,
                                     GameBoard* board) {
    std::cout << "\n请选择行动:" << std::endl;
    std::cout << "1. 建造建筑" << std::endl;
    std::cout << "2. 建造奇迹" << std::endl;
    std::cout << "3. 弃牌换金币" << std::endl;
    
    int actionChoice = getIntInput("选择行动", 1, 3);
    
    // 显示可用卡牌
    std::cout << "\n可用卡牌:" << std::endl;
    for (size_t i = 0; i < availableCards.size(); i++) {
        Card* card = availableCards[i];
        std::cout << (i + 1) << ". " << card->getDescription();
        
        // 显示是否可以建造
        bool canAfford = player->canAfford(card->getCost(), opponent);
        bool isFree = card->hasFreeConstruction(player);
        
        if (isFree) {
            std::cout << " [免费建造]";
        } else if (canAfford) {
            int cost = player->calculateResourceCost(card->getCost(), opponent);
            std::cout << " [可建造,花费" << cost << "金币]";
        } else {
            std::cout << " [金币不足]";
        }
        
        std::cout << std::endl;
    }
    
    int cardChoice = getIntInput("选择卡牌", 1, availableCards.size());
    Card* selectedCard = availableCards[cardChoice - 1];
    
    switch (actionChoice) {
        case 1: {
            // 建造建筑
            return new Action(ActionType::BUILD_STRUCTURE, selectedCard);
        }
        
        case 2: {
            // 建造奇迹
            std::cout << "\n可用奇迹:" << std::endl;
            const auto& wonders = player->getAvailableWonders();
            std::vector<WonderCard*> unbuiltWonders;
            
            for (auto* wonder : wonders) {
                if (!wonder->isBuilt()) {
                    unbuiltWonders.push_back(wonder);
                }
            }
            
            if (unbuiltWonders.empty()) {
                std::cout << "没有可建造的奇迹!" << std::endl;
                return getPlayerAction(player, opponent, availableCards, board);
            }
            
            for (size_t i = 0; i < unbuiltWonders.size(); i++) {
                WonderCard* wonder = unbuiltWonders[i];
                std::cout << (i + 1) << ". " << wonder->getDescription();
                
                bool canAfford = player->canAfford(wonder->getCost(), opponent);
                if (canAfford) {
                    int cost = player->calculateResourceCost(wonder->getCost(), opponent);
                    std::cout << " [可建造,花费" << cost << "金币]";
                } else {
                    std::cout << " [金币不足]";
                }
                
                std::cout << std::endl;
            }
            
            int wonderChoice = getIntInput("选择奇迹", 1, unbuiltWonders.size());
            WonderCard* selectedWonder = unbuiltWonders[wonderChoice - 1];
            
            return new Action(ActionType::BUILD_WONDER, selectedCard, selectedWonder);
        }
        
        case 3: {
            // 弃牌换金币
            int coins = 2 + opponent->countCardsByType(CardType::COMMERCIAL);
            std::cout << "将获得 " << coins << " 金币" << std::endl;
            return new Action(ActionType::DISCARD_FOR_COINS, selectedCard);
        }
    }
    
    return nullptr;
}
