#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"
#include "PlayerStrategy.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string& name);
    Action* makeDecision(GameState& state) override;
};

class AIPlayer : public Player {
public:
    AIPlayer(const std::string& name, AIStrategy* aiStrategy);
    Action* makeDecision(GameState& state) override;
};

#endif // HUMAN_PLAYER_H
