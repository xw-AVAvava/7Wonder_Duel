#ifndef WONDER_CARD_H
#define WONDER_CARD_H

#include "Card.h"
#include "../Types.h"
#include <vector>

class WonderCard : public Card {
private:
    std::string wonderName;
    int victoryPoints;
    bool built;
    std::vector<WonderEffect> effects;
    
    // 效果参数
    int coinsReward;
    int militaryPowerBonus;
    bool allowReplay;
    bool destroyOpponentCard;
    bool recycleCard;
    bool reduceTradeCost;
    int opponentCoinLoss;

public:
    WonderCard(const std::string& wonderName);
    
    void apply(Player* player, Player* opponent, GameBoard* board) override;
    int getVictoryPoints(Player* player, Player* opponent) const override;
    Card* clone() const override;
    
    bool isBuilt() const { return built; }
    void build() { built = true; }
    
    void addEffect(WonderEffect effect);
    void setVictoryPoints(int vp) { victoryPoints = vp; }
    void setCoinsReward(int coins) { coinsReward = coins; }
    void setMilitaryPowerBonus(int power) { militaryPowerBonus = power; }
    void setAllowReplay(bool replay) { allowReplay = replay; }
    void setDestroyOpponentCard(bool destroy) { destroyOpponentCard = destroy; }
    void setRecycleCard(bool recycle) { recycleCard = recycle; }
    void setReduceTradeCost(bool reduce) { reduceTradeCost = reduce; }
    void setOpponentCoinLoss(int loss) { opponentCoinLoss = loss; }
    
    bool hasReplayEffect() const { return allowReplay; }
    bool hasDestroyEffect() const { return destroyOpponentCard; }
    bool hasRecycleEffect() const { return recycleCard; }
    
    std::string getDescription() const override;
};

#endif // WONDER_CARD_H
