#include "../../include/game/ProgressToken.h"
#include "../../include/player/Player.h"
#include <sstream>

ProgressToken::ProgressToken(ProgressType type, const std::string& name)
    : type(type), name(name) {}

void ProgressToken::apply(Player* player) {
    switch (type) {
        case ProgressType::AGRICULTURE:
            // 每回合结束获得6金币(在Game类中处理)
            break;
            
        case ProgressType::ARCHITECTURE:
            // 未来建造奇迹减少2资源(在建造时检查)
            break;
            
        case ProgressType::ECONOMY:
            // 财富立即翻倍
            player->addCoins(player->getCoins());
            break;
            
        case ProgressType::LAW:
            // 科学符号视为一对(在检查时处理)
            break;
            
        case ProgressType::MASONRY:
            // 未来建造蓝色建筑免费(在建造时检查)
            break;
            
        case ProgressType::MATHEMATICS:
            // 游戏结束时每个进度标记3点(在计分时处理)
            break;
            
        case ProgressType::PHILOSOPHY:
            // 游戏结束时7点(在计分时处理)
            break;
            
        case ProgressType::STRATEGY:
            // 军事标记给予额外1盾(在军事计算时处理)
            break;
            
        case ProgressType::THEOLOGY:
            // 立即再行动一次(在Game类中处理)
            break;
            
        case ProgressType::URBANISM:
            // 立即获得6金币 + 从弃牌堆选择一张建造
            player->addCoins(6);
            // 弃牌堆选择在Game类中处理
            break;
    }
}

int ProgressToken::getVictoryPoints(Player* player) const {
    switch (type) {
        case ProgressType::MATHEMATICS:
            // 每个进度标记3点
            return player->getProgressTokens().size() * 3;
            
        case ProgressType::PHILOSOPHY:
            return 7;
            
        default:
            return 0;
    }
}

std::string ProgressToken::getDescription() const {
    std::stringstream ss;
    ss << "[进度标记] " << progressTypeToString(type);
    
    switch (type) {
        case ProgressType::AGRICULTURE:
            ss << " - 每回合结束获得6金币";
            break;
        case ProgressType::ARCHITECTURE:
            ss << " - 建造奇迹减少2资源";
            break;
        case ProgressType::ECONOMY:
            ss << " - 财富立即翻倍";
            break;
        case ProgressType::LAW:
            ss << " - 科学符号视为一对";
            break;
        case ProgressType::MASONRY:
            ss << " - 蓝色建筑免费";
            break;
        case ProgressType::MATHEMATICS:
            ss << " - 游戏结束时每个进度标记3点";
            break;
        case ProgressType::PHILOSOPHY:
            ss << " - 游戏结束时7点";
            break;
        case ProgressType::STRATEGY:
            ss << " - 军事标记额外1盾";
            break;
        case ProgressType::THEOLOGY:
            ss << " - 立即再行动一次";
            break;
        case ProgressType::URBANISM:
            ss << " - 获得6金币+回收弃牌";
            break;
    }
    
    return ss.str();
}

MilitaryToken::MilitaryToken(int position, int coinsReward, bool isOpponentLoss)
    : position(position), coinsReward(coinsReward), isOpponentLoss(isOpponentLoss) {}

void MilitaryToken::apply(Player* player, Player* opponent) {
    if (isOpponentLoss) {
        opponent->removeCoins(coinsReward);
    } else {
        player->addCoins(coinsReward);
    }
}
