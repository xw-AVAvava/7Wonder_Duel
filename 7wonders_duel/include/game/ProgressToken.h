#ifndef PROGRESS_TOKEN_H
#define PROGRESS_TOKEN_H

#include "../Types.h"
#include "../Forward.h"
#include <string>

class ProgressToken {
private:
    ProgressType type;
    std::string name;

public:
    ProgressToken(ProgressType type, const std::string& name);
    
    void apply(Player* player);
    int getVictoryPoints(Player* player) const;
    ProgressType getType() const { return type; }
    std::string getName() const { return name; }
    std::string getDescription() const;
};

class MilitaryToken {
private:
    int position;           // 在军事轨道上的位置
    int coinsReward;        // 金币奖励
    bool isOpponentLoss;    // 是否是对手失去金币

public:
    MilitaryToken(int position, int coinsReward, bool isOpponentLoss);
    
    void apply(Player* player, Player* opponent);
    int getPosition() const { return position; }
    int getCoinsReward() const { return coinsReward; }
};

#endif // PROGRESS_TOKEN_H
