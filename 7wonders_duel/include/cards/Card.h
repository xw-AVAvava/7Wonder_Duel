#ifndef CARD_H
#define CARD_H

#include "../Types.h"
#include "../Forward.h"
#include "../resources/Cost.h"
#include <string>

class Card {
protected:
    std::string name;
    CardType type;
    int age;
    Cost cost;
    std::string chainSymbol;      // 这张卡提供的链接符号
    std::string chainedFrom;      // 可以从哪张卡免费建造

public:
    Card(const std::string& name, CardType type, int age);
    virtual ~Card() = default;
    
    // 纯虚函数
    virtual void apply(Player* player, Player* opponent, GameBoard* board) = 0;
    virtual int getVictoryPoints(Player* player, Player* opponent) const = 0;
    virtual Card* clone() const = 0;
    
    // Getter方法
    std::string getName() const { return name; }
    CardType getType() const { return type; }
    int getAge() const { return age; }
    const Cost& getCost() const { return cost; }
    std::string getChainSymbol() const { return chainSymbol; }
    std::string getChainedFrom() const { return chainedFrom; }
    
    // Setter方法
    void setCost(const Cost& c) { cost = c; }
    void setChainSymbol(const std::string& symbol) { chainSymbol = symbol; }
    void setChainedFrom(const std::string& from) { chainedFrom = from; }
    
    // 检查是否可以免费建造
    bool hasFreeConstruction(Player* player) const;
    
    // 显示卡牌信息
    virtual std::string getDescription() const;
};

#endif // CARD_H
