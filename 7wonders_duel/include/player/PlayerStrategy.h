#ifndef PLAYER_STRATEGY_H
#define PLAYER_STRATEGY_H

#include "../Forward.h"
#include "../Types.h"
#include <vector>

// 游戏状态结构
struct GameState {
    Player* currentPlayer;
    Player* opponent;
    GameBoard* board;
    std::vector<Card*> availableCards;
    int currentAge;
    std::vector<Card*> discardPile;
};

// 玩家行动结构
class Action {
public:
    ActionType type;
    Card* targetCard;
    WonderCard* targetWonder;
    
    Action(ActionType type, Card* card = nullptr, WonderCard* wonder = nullptr)
        : type(type), targetCard(card), targetWonder(wonder) {}
};

// 策略接口
class PlayerStrategy {
public:
    virtual ~PlayerStrategy() = default;
    virtual Action* chooseAction(GameState& state) = 0;
};

// 人类策略(通过UI交互)
class HumanStrategy : public PlayerStrategy {
public:
    Action* chooseAction(GameState& state) override;
};

// AI策略基类
class AIStrategy : public PlayerStrategy {
protected:
    double evaluateCard(Card* card, GameState& state);
    double evaluateBuildAction(Card* card, GameState& state);
    double evaluateWonderAction(WonderCard* wonder, GameState& state);
};

// 随机AI
class RandomAI : public AIStrategy {
public:
    Action* chooseAction(GameState& state) override;
};

// 贪心AI
class GreedyAI : public AIStrategy {
public:
    Action* chooseAction(GameState& state) override;
    
private:
    double calculateCardValue(Card* card, GameState& state);
};

#endif // PLAYER_STRATEGY_H
