#ifndef VICTORY_CONDITION_H
#define VICTORY_CONDITION_H

#include "../Forward.h"
#include "../Types.h"

class VictoryCondition {
public:
    bool checkMilitaryVictory(MilitaryTrack* track) const;
    bool checkScientificVictory(Player* player) const;
    Player* calculateCivilianVictory(Player* p1, Player* p2) const;
    
    int calculateTotalPoints(Player* player, Player* opponent) const;
    int calculateMilitaryPoints(MilitaryTrack* track, Player* player, Player* opponent) const;
};

#endif // VICTORY_CONDITION_H
