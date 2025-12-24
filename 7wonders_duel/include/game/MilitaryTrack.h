#ifndef MILITARY_TRACK_H
#define MILITARY_TRACK_H

#include "../Forward.h"
#include <map>
#include <string>

class MilitaryTrack {
private:
    int conflictPawnPosition;  // -9 到 +9, 0是中心
    std::map<int, MilitaryToken*> militaryTokens;
    bool militaryTokensTriggered[4];  // 记录哪些军事标记已经触发

public:
    MilitaryTrack();
    ~MilitaryTrack();
    
    void initialize();
    void moveConflictPawn(int spaces, Player* activePlayer, Player* opponent);
    bool checkMilitaryVictory() const;
    int getPosition() const { return conflictPawnPosition; }
    
    void addMilitaryToken(int position, MilitaryToken* token);
    MilitaryToken* getTokenAtPosition(int position);
    
    std::string getVisualRepresentation() const;
};

#endif // MILITARY_TRACK_H
