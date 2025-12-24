#include "../../include/player/HumanPlayer.h"

HumanPlayer::HumanPlayer(const std::string& name)
    : Player(name, new HumanStrategy()) {}

Action* HumanPlayer::makeDecision(GameState& state) {
    return strategy->chooseAction(state);
}

AIPlayer::AIPlayer(const std::string& name, AIStrategy* aiStrategy)
    : Player(name, aiStrategy) {}

Action* AIPlayer::makeDecision(GameState& state) {
    return strategy->chooseAction(state);
}
