#ifndef PLAYER_H
#define PLAYER_H

#include "../Types.h"
#include "../Forward.h"
#include <string>
#include <vector>
#include <map>

class Player {
protected:
    std::string name;
    PlayerStrategy* strategy;
    std::vector<Card*> buildings;
    std::vector<WonderCard*> wonders;
    std::vector<WonderCard*> availableWonders;  // 可建造的奇迹
    int coins;
    int militaryPower;
    std::map<ScientificSymbol, int> scientificSymbols;
    std::vector<ProgressToken*> progressTokens;
    
    // 商业效果
    int rawMaterialDiscount;        // 原材料购买折扣
    int manufacturedGoodDiscount;   // 制成品购买折扣

public:
    Player(const std::string& name, PlayerStrategy* strategy);
    virtual ~Player();
    
    // 纯虚函数
    virtual Action* makeDecision(GameState& state) = 0;
    
    // 建筑和奇迹管理
    void addBuilding(Card* card);
    void buildWonder(WonderCard* wonder, Card* usedCard);
    
    // 资源管理
    void addCoins(int amount);
    bool removeCoins(int amount);
    
    // 军事
    void addMilitaryPower(int power);
    
    // 科学
    void addScientificSymbol(ScientificSymbol symbol);
    bool hasScientificVictory() const;
    int countScientificPairs() const;  // 计算相同符号对数量
    
    // 进度标记
    void addProgressToken(ProgressToken* token);
    bool hasProgressToken(ProgressType type) const;
    
    // 商业效果
    void setRawMaterialDiscount(int discount);
    void setManufacturedGoodDiscount(int discount);
    int getRawMaterialDiscount() const { return rawMaterialDiscount; }
    int getManufacturedGoodDiscount() const { return manufacturedGoodDiscount; }
    
    // 计算胜利点数
    int calculateVictoryPoints(Player* opponent) const;
    
    // 资源检查
    bool canAfford(const Cost& cost, Player* opponent) const;
    int calculateResourceCost(const Cost& cost, Player* opponent) const;
    std::map<ResourceType, int> getAvailableResources() const;
    
    // 查询方法
    const std::vector<Card*>& getBuildings() const { return buildings; }
    const std::vector<WonderCard*>& getWonders() const { return wonders; }
    const std::vector<WonderCard*>& getAvailableWonders() const { return availableWonders; }
    int getCoins() const { return coins; }
    int getMilitaryPower() const { return militaryPower; }
    const std::map<ScientificSymbol, int>& getScientificSymbols() const { return scientificSymbols; }
    const std::vector<ProgressToken*>& getProgressTokens() const { return progressTokens; }
    std::string getName() const { return name; }
    
    // 卡牌统计
    int countCardsByType(CardType type) const;
    bool hasBuilding(const std::string& buildingName) const;
    
    // 奇迹管理
    void addAvailableWonder(WonderCard* wonder);
    WonderCard* getUnbuiltWonder() const;  // 获取一个未建造的奇迹
};

#endif // PLAYER_H
