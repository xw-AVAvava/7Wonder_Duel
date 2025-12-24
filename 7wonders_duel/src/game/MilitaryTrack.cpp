#include "../../include/game/MilitaryTrack.h"
#include "../../include/game/ProgressToken.h"
#include "../../include/player/Player.h"
#include <sstream>
#include <cstring>

MilitaryTrack::MilitaryTrack() : conflictPawnPosition(0) {
    std::memset(militaryTokensTriggered, false, sizeof(militaryTokensTriggered));
}

MilitaryTrack::~MilitaryTrack() {
    for (auto& pair : militaryTokens) {
        delete pair.second;
    }
}

void MilitaryTrack::initialize() {
    conflictPawnPosition = 0;
    std::memset(militaryTokensTriggered, false, sizeof(militaryTokensTriggered));
    
    // 创建军事标记
    // 位置-3: 玩家2获得2金币
    militaryTokens[-3] = new MilitaryToken(-3, 2, false);
    
    // 位置-6: 玩家2获得5金币
    militaryTokens[-6] = new MilitaryToken(-6, 5, false);
    
    // 位置+3: 玩家1获得2金币(或玩家2失去2金币)
    militaryTokens[3] = new MilitaryToken(3, 2, true);
    
    // 位置+6: 玩家1获得5金币(或玩家2失去5金币)
    militaryTokens[6] = new MilitaryToken(6, 5, true);
}

void MilitaryTrack::moveConflictPawn(int spaces, Player* activePlayer, Player* opponent) {
    int oldPosition = conflictPawnPosition;
    conflictPawnPosition += spaces;
    
    // 限制在-9到+9之间
    if (conflictPawnPosition > 9) conflictPawnPosition = 9;
    if (conflictPawnPosition < -9) conflictPawnPosition = -9;
    
    // 检查是否触发军事标记
    if (spaces > 0) {
        // 向正方向移动
        for (int pos = oldPosition + 1; pos <= conflictPawnPosition; pos++) {
            if (militaryTokens.find(pos) != militaryTokens.end()) {
                int tokenIndex = -1;
                if (pos == 3) tokenIndex = 2;
                else if (pos == 6) tokenIndex = 3;
                
                if (tokenIndex >= 0 && !militaryTokensTriggered[tokenIndex]) {
                    militaryTokens[pos]->apply(activePlayer, opponent);
                    militaryTokensTriggered[tokenIndex] = true;
                }
            }
        }
    } else if (spaces < 0) {
        // 向负方向移动
        for (int pos = oldPosition - 1; pos >= conflictPawnPosition; pos--) {
            if (militaryTokens.find(pos) != militaryTokens.end()) {
                int tokenIndex = -1;
                if (pos == -3) tokenIndex = 0;
                else if (pos == -6) tokenIndex = 1;
                
                if (tokenIndex >= 0 && !militaryTokensTriggered[tokenIndex]) {
                    militaryTokens[pos]->apply(opponent, activePlayer);  // 注意这里是opponent获益
                    militaryTokensTriggered[tokenIndex] = true;
                }
            }
        }
    }
}

bool MilitaryTrack::checkMilitaryVictory() const {
    return conflictPawnPosition == 9 || conflictPawnPosition == -9;
}

void MilitaryTrack::addMilitaryToken(int position, MilitaryToken* token) {
    militaryTokens[position] = token;
}

MilitaryToken* MilitaryTrack::getTokenAtPosition(int position) {
    if (militaryTokens.find(position) != militaryTokens.end()) {
        return militaryTokens[position];
    }
    return nullptr;
}

std::string MilitaryTrack::getVisualRepresentation() const {
    std::stringstream ss;
    ss << "\n军事轨道:\n";
    ss << "玩家2首都 ";
    
    for (int i = -9; i <= 9; i++) {
        if (i == conflictPawnPosition) {
            ss << "[X]";
        } else if (militaryTokens.find(i) != militaryTokens.end()) {
            ss << "[T]";
        } else if (i == 0) {
            ss << "[0]";
        } else {
            ss << "---";
        }
        
        if (i < 9) ss << "-";
    }
    
    ss << " 玩家1首都\n";
    ss << "当前位置: " << conflictPawnPosition << "\n";
    
    return ss.str();
}
