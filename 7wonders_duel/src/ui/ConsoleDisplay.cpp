#include "../../include/ui/ConsoleDisplay.h"
#include "../../include/player/Player.h"
#include "../../include/game/GameBoard.h"
#include "../../include/cards/Card.h"
#include "../../include/cards/WonderCard.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

void ConsoleDisplay::displayGameState(GameBoard* board, Player* currentPlayer, Player* opponent) {
    // 显示军事轨道
    std::cout << board->getMilitaryTrack()->getVisualRepresentation() << std::endl;
    
    // 显示玩家信息
    displayPlayerInfo(currentPlayer, opponent);
    
    // 显示可用卡牌
    auto availableCards = board->getAccessibleCards();
    std::cout << "\n可用卡牌 (" << availableCards.size() << "张):" << std::endl;
    displayAvailableCards(availableCards);
}

void ConsoleDisplay::displayPlayerInfo(Player* player, Player* opponent) {
    std::cout << "\n" << std::string(40, '-') << std::endl;
    std::cout << "【" << player->getName() << "】" << std::endl;
    std::cout << "金币: " << player->getCoins() << std::endl;
    std::cout << "军事力量: " << player->getMilitaryPower() << "盾" << std::endl;
    
    // 显示科学符号
    const auto& symbols = player->getScientificSymbols();
    if (!symbols.empty()) {
        std::cout << "科学符号: ";
        for (const auto& pair : symbols) {
            if (pair.second > 0) {
                std::cout << scientificSymbolToString(pair.first) << "×" << pair.second << " ";
            }
        }
        std::cout << std::endl;
    }
    
    // 显示建筑数量
    std::cout << "建筑数量: " << player->getBuildings().size() << std::endl;
    std::cout << "  - 原材料: " << player->countCardsByType(CardType::RAW_MATERIAL) << std::endl;
    std::cout << "  - 制成品: " << player->countCardsByType(CardType::MANUFACTURED_GOOD) << std::endl;
    std::cout << "  - 平民: " << player->countCardsByType(CardType::CIVILIAN) << std::endl;
    std::cout << "  - 科学: " << player->countCardsByType(CardType::SCIENTIFIC) << std::endl;
    std::cout << "  - 商业: " << player->countCardsByType(CardType::COMMERCIAL) << std::endl;
    std::cout << "  - 军事: " << player->countCardsByType(CardType::MILITARY) << std::endl;
    
    // 显示奇迹
    std::cout << "已建造奇迹: " << player->getWonders().size() << std::endl;
    for (const auto* wonder : player->getWonders()) {
        std::cout << "  - " << wonder->getName() << std::endl;
    }
    
    // 显示进度标记
    if (!player->getProgressTokens().empty()) {
        std::cout << "进度标记: ";
        for (const auto* token : player->getProgressTokens()) {
            std::cout << token->getName() << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << std::string(40, '-') << std::endl;
    
    // 简要显示对手信息
    std::cout << "\n【对手: " << opponent->getName() << "】" << std::endl;
    std::cout << "金币: " << opponent->getCoins() 
              << " | 军事: " << opponent->getMilitaryPower()
              << " | 建筑: " << opponent->getBuildings().size() << std::endl;
}

void ConsoleDisplay::displayAvailableCards(const std::vector<Card*>& cards) {
    for (size_t i = 0; i < cards.size(); i++) {
        std::cout << std::setw(2) << (i + 1) << ". " << cards[i]->getDescription() << std::endl;
    }
}

void ConsoleDisplay::displayFinalScores(Player* p1, Player* p2, GameBoard* board) {
    displaySeparator('-', 60);
    std::cout << "详细得分统计:" << std::endl;
    displaySeparator('-', 60);
    
    for (Player* player : {p1, p2}) {
        Player* opponent = (player == p1) ? p2 : p1;
        
        std::cout << "\n" << player->getName() << ":" << std::endl;
        
        int buildingPoints = 0;
        for (const auto* card : player->getBuildings()) {
            buildingPoints += card->getVictoryPoints(player, opponent);
        }
        std::cout << "  建筑点数: " << buildingPoints << std::endl;
        
        int wonderPoints = 0;
        for (const auto* wonder : player->getWonders()) {
            wonderPoints += wonder->getVictoryPoints(player, opponent);
        }
        std::cout << "  奇迹点数: " << wonderPoints << std::endl;
        
        int progressPoints = 0;
        for (const auto* token : player->getProgressTokens()) {
            progressPoints += token->getVictoryPoints(player);
        }
        std::cout << "  进度标记点数: " << progressPoints << std::endl;
        
        int coinPoints = player->getCoins() / 3;
        std::cout << "  金库点数: " << coinPoints << " (" << player->getCoins() << "金币)" << std::endl;
        
        int total = buildingPoints + wonderPoints + progressPoints + coinPoints;
        std::cout << "  总计: " << total << "点" << std::endl;
    }
}

void ConsoleDisplay::clearScreen() {
    // 跨平台清屏
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ConsoleDisplay::displaySeparator(char c, int length) {
    std::cout << std::string(length, c) << std::endl;
}
