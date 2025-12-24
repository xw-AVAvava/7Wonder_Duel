#include "../../include/cards/Card.h"
#include "../../include/player/Player.h"
#include <sstream>

Card::Card(const std::string& name, CardType type, int age)
    : name(name), type(type), age(age) {}

bool Card::hasFreeConstruction(Player* player) const {
    if (chainedFrom.empty()) {
        return false;
    }
    
    // 检查玩家是否已经建造了前置建筑
    const auto& buildings = player->getBuildings();
    for (const auto& card : buildings) {
        if (card->getChainSymbol() == chainedFrom) {
            return true;
        }
    }
    
    return false;
}

std::string Card::getDescription() const {
    std::stringstream ss;
    ss << "[" << cardTypeToString(type) << "] " << name;
    ss << " (时代" << age << ")";
    
    if (!cost.isEmpty()) {
        ss << " - 成本: " << cost.toString();
    } else {
        ss << " - 免费";
    }
    
    if (!chainedFrom.empty()) {
        ss << " [可链接]";
    }
    
    return ss.str();
}
