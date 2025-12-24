#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "../Forward.h"
#include "../player/PlayerStrategy.h"
#include <string>
#include <vector>

class InputHandler {
public:
    int getIntInput(const std::string& prompt, int min, int max);
    std::string getStringInput(const std::string& prompt);
    
    Action* getPlayerAction(Player* player, Player* opponent, 
                           const std::vector<Card*>& availableCards,
                           GameBoard* board);
    
private:
    bool validateInput(const std::string& input, int& value, int min, int max);
};

#endif // INPUT_HANDLER_H
