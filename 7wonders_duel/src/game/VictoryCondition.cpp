#include "../../include/game/VictoryCondition.h"
#include "../../include/player/Player.h"
#include "../../include/game/MilitaryTrack.h"

bool VictoryCondition::checkMilitaryVictory(MilitaryTrack* track) const {
    return track->checkMilitaryVictory();
}

bool VictoryCondition::checkScientificVictory(Player* player) const {
    return player->hasScientificVictory();
}

Player* VictoryCondition::calculateCivilianVictory(Player* p1, Player* p2) const {
    int p1Points = calculateTotalPoints(p1, p2);
    int p2Points = calculateTotalPoints(p2, p1);
    
    if (p1Points > p2Points) {
        return p1;
    } else if (p2Points > p1Points) {
        return p2;
    }
    
    return nullptr;  // 平局
}

int VictoryCondition::calculateTotalPoints(Player* player, Player* opponent) const {
    return player->calculateVictoryPoints(opponent);
}

int VictoryCondition::calculateMilitaryPoints(MilitaryTrack* track, Player* player, Player* opponent) const {
    int position = track->getPosition();
    
    // 简化:根据位置给予军事点数
    // 实际游戏中军事点数来自获得的军事标记
    // 这里暂时返回0,因为军事标记已经给予了金币奖励
    return 0;
}
