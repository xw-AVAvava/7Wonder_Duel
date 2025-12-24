#ifndef CARD_FACTORY_H
#define CARD_FACTORY_H

#include "Card.h"
#include "AllCards.h"
#include "WonderCard.h"
#include <vector>

class CardFactory {
public:
    // 创建各时代的卡牌组
    static std::vector<Card*> createAgeIDeck();
    static std::vector<Card*> createAgeIIDeck();
    static std::vector<Card*> createAgeIIIDeck();
    
    // 创建公会卡(时代III随机选择3张)
    static std::vector<GuildCard*> createAllGuildCards();
    
    // 创建所有奇迹卡
    static std::vector<WonderCard*> createAllWonderCards();
    
private:
    // 辅助函数:创建带成本的卡牌
    template<typename T>
    static T* createCardWithCost(T* card, const std::vector<std::pair<ResourceType, int>>& resources, int coins = 0);
};

#endif // CARD_FACTORY_H
