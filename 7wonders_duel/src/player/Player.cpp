#include "../../include/player/Player.h"
#include "../../include/cards/Card.h"
#include "../../include/cards/WonderCard.h"
#include "../../include/game/ProgressToken.h"
#include <algorithm>
#include <set>

Player::Player(const std::string& name, PlayerStrategy* strategy)
    : name(name), strategy(strategy), coins(7), militaryPower(0),
      rawMaterialDiscount(0), manufacturedGoodDiscount(0) {}

Player::~Player() {
    // 注意: Card和WonderCard的内存由Game或CardFactory管理
    // ProgressToken的内存由GameBoard管理
    // 只删除strategy
    delete strategy;
}

void Player::addBuilding(Card* card) {
    buildings.push_back(card);
}

void Player::buildWonder(WonderCard* wonder, Card* usedCard) {
    wonders.push_back(wonder);
    // usedCard被弃置,不加入buildings
}

void Player::addCoins(int amount) {
    coins += amount;
}

bool Player::removeCoins(int amount) {
    if (coins >= amount) {
        coins -= amount;
        return true;
    }
    return false;
}

void Player::addMilitaryPower(int power) {
    militaryPower += power;
}

void Player::addScientificSymbol(ScientificSymbol symbol) {
    scientificSymbols[symbol]++;
}

bool Player::hasScientificVictory() const {
    // 收集6个不同的科学符号
    int differentSymbols = 0;
    for (const auto& pair : scientificSymbols) {
        if (pair.second > 0) {
            differentSymbols++;
        }
    }
    return differentSymbols >= 6;
}

int Player::countScientificPairs() const {
    int pairs = 0;
    for (const auto& pair : scientificSymbols) {
        pairs += pair.second / 2;
    }
    return pairs;
}

void Player::addProgressToken(ProgressToken* token) {
    progressTokens.push_back(token);
}

bool Player::hasProgressToken(ProgressType type) const {
    for (const auto& token : progressTokens) {
        if (token->getType() == type) {
            return true;
        }
    }
    return false;
}

void Player::setRawMaterialDiscount(int discount) {
    rawMaterialDiscount = std::max(rawMaterialDiscount, discount);
}

void Player::setManufacturedGoodDiscount(int discount) {
    manufacturedGoodDiscount = std::max(manufacturedGoodDiscount, discount);
}

int Player::calculateVictoryPoints(Player* opponent) const {
    int total = 0;
    
    // 建筑点数
    for (const auto& card : buildings) {
        total += card->getVictoryPoints(const_cast<Player*>(this), opponent);
    }
    
    // 奇迹点数
    for (const auto& wonder : wonders) {
        total += wonder->getVictoryPoints(const_cast<Player*>(this), opponent);
    }
    
    // 进度标记点数
    for (const auto& token : progressTokens) {
        total += token->getVictoryPoints(const_cast<Player*>(this));
    }
    
    // 金库点数(每3金币1分)
    total += coins / 3;
    
    return total;
}

std::map<ResourceType, int> Player::getAvailableResources() const {
    std::map<ResourceType, int> resources;
    
    for (const auto& card : buildings) {
        CardType type = card->getType();
        if (type == CardType::RAW_MATERIAL) {
            // 需要向下转型获取资源信息
            // 这里简化处理,实际应该使用dynamic_cast
        } else if (type == CardType::MANUFACTURED_GOOD) {
            // 同上
        }
    }
    
    return resources;
}

bool Player::canAfford(const Cost& cost, Player* opponent) const {
    return calculateResourceCost(cost, opponent) <= coins;
}

int Player::calculateResourceCost(const Cost& cost, Player* opponent) const {
    int totalCost = cost.getCoins();
    
    // 获取自己的资源
    std::map<ResourceType, int> availableResources = getAvailableResources();
    
    // 计算需要购买的资源
    for (const auto& pair : cost.getResources()) {
        ResourceType type = pair.first;
        int needed = pair.second;
        int available = availableResources[type];
        int toBuy = std::max(0, needed - available);
        
        if (toBuy > 0) {
            // 基础价格2金币/资源
            int pricePerResource = 2;
            
            // 对手每拥有一张该资源的卡牌,价格+1
            int opponentCards = 0;
            for (const auto& card : opponent->getBuildings()) {
                // 简化:需要检查卡牌是否生产该资源
                // 这里暂时不实现详细逻辑
            }
            pricePerResource += opponentCards;
            
            // 应用折扣
            if (type == ResourceType::WOOD || type == ResourceType::STONE || type == ResourceType::CLAY) {
                pricePerResource -= rawMaterialDiscount;
            } else {
                pricePerResource -= manufacturedGoodDiscount;
            }
            
            pricePerResource = std::max(0, pricePerResource);
            totalCost += toBuy * pricePerResource;
        }
    }
    
    return totalCost;
}

int Player::countCardsByType(CardType type) const {
    int count = 0;
    for (const auto& card : buildings) {
        if (card->getType() == type) {
            count++;
        }
    }
    return count;
}

bool Player::hasBuilding(const std::string& buildingName) const {
    for (const auto& card : buildings) {
        if (card->getName() == buildingName) {
            return true;
        }
    }
    return false;
}

void Player::addAvailableWonder(WonderCard* wonder) {
    availableWonders.push_back(wonder);
}

WonderCard* Player::getUnbuiltWonder() const {
    for (auto* wonder : availableWonders) {
        if (!wonder->isBuilt()) {
            return wonder;
        }
    }
    return nullptr;
}
