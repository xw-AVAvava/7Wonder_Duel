#ifndef ALL_CARDS_H
#define ALL_CARDS_H

#include "Card.h"
#include "../Types.h"

// 原材料卡
class RawMaterialCard : public Card {
private:
    ResourceType resource;
    int quantity;

public:
    RawMaterialCard(const std::string& name, int age, ResourceType resource, int quantity = 1);
    
    void apply(Player* player, Player* opponent, GameBoard* board) override;
    int getVictoryPoints(Player* player, Player* opponent) const override;
    Card* clone() const override;
    
    ResourceType getResource() const { return resource; }
    int getQuantity() const { return quantity; }
    std::string getDescription() const override;
};

// 制成品卡
class ManufacturedGoodCard : public Card {
private:
    ResourceType resource;
    int quantity;

public:
    ManufacturedGoodCard(const std::string& name, int age, ResourceType resource, int quantity = 1);
    
    void apply(Player* player, Player* opponent, GameBoard* board) override;
    int getVictoryPoints(Player* player, Player* opponent) const override;
    Card* clone() const override;
    
    ResourceType getResource() const { return resource; }
    int getQuantity() const { return quantity; }
    std::string getDescription() const override;
};

// 平民建筑卡
class CivilianCard : public Card {
private:
    int victoryPoints;

public:
    CivilianCard(const std::string& name, int age, int victoryPoints);
    
    void apply(Player* player, Player* opponent, GameBoard* board) override;
    int getVictoryPoints(Player* player, Player* opponent) const override;
    Card* clone() const override;
    std::string getDescription() const override;
};

// 科学建筑卡
class ScientificCard : public Card {
private:
    ScientificSymbol symbol;
    int victoryPoints;

public:
    ScientificCard(const std::string& name, int age, ScientificSymbol symbol, int victoryPoints);
    
    void apply(Player* player, Player* opponent, GameBoard* board) override;
    int getVictoryPoints(Player* player, Player* opponent) const override;
    Card* clone() const override;
    
    ScientificSymbol getSymbol() const { return symbol; }
    std::string getDescription() const override;
};

// 军事建筑卡
class MilitaryCard : public Card {
private:
    int militaryPower;

public:
    MilitaryCard(const std::string& name, int age, int militaryPower);
    
    void apply(Player* player, Player* opponent, GameBoard* board) override;
    int getVictoryPoints(Player* player, Player* opponent) const override;
    Card* clone() const override;
    
    int getMilitaryPower() const { return militaryPower; }
    std::string getDescription() const override;
};

// 商业建筑卡
class CommercialCard : public Card {
private:
    CommercialEffect effect;
    int victoryPoints;
    int immediateCoins;
    // 额外效果参数
    ResourceType producedResource;  // 如果生产资源
    int coinsPerCard;               // 每张特定卡牌的金币
    CardType countedCardType;       // 计数的卡牌类型

public:
    CommercialCard(const std::string& name, int age, CommercialEffect effect);
    
    void apply(Player* player, Player* opponent, GameBoard* board) override;
    int getVictoryPoints(Player* player, Player* opponent) const override;
    Card* clone() const override;
    
    void setVictoryPoints(int vp) { victoryPoints = vp; }
    void setImmediateCoins(int coins) { immediateCoins = coins; }
    void setProducedResource(ResourceType res) { producedResource = res; }
    void setCoinsPerCard(int coins, CardType type) { 
        coinsPerCard = coins; 
        countedCardType = type; 
    }
    
    std::string getDescription() const override;
};

// 公会卡
class GuildCard : public Card {
private:
    GuildType guildType;
    int pointsPerCard;

public:
    GuildCard(const std::string& name, GuildType guildType, int pointsPerCard);
    
    void apply(Player* player, Player* opponent, GameBoard* board) override;
    int getVictoryPoints(Player* player, Player* opponent) const override;
    Card* clone() const override;
    
    GuildType getGuildType() const { return guildType; }
    std::string getDescription() const override;
    
private:
    int calculateGuildPoints(Player* player, Player* opponent) const;
};

#endif // ALL_CARDS_H
