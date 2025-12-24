#include "../../include/cards/AllCards.h"
#include "../../include/player/Player.h"
#include "../../include/game/GameBoard.h"
#include <sstream>

// ==================== RawMaterialCard ====================
RawMaterialCard::RawMaterialCard(const std::string& name, int age, ResourceType resource, int quantity)
    : Card(name, CardType::RAW_MATERIAL, age), resource(resource), quantity(quantity) {}

void RawMaterialCard::apply(Player* player, Player* opponent, GameBoard* board) {
    // 原材料卡不需要特殊应用逻辑,资源在查询时计算
}

int RawMaterialCard::getVictoryPoints(Player* player, Player* opponent) const {
    return 0;  // 原材料卡不提供胜利点数
}

Card* RawMaterialCard::clone() const {
    RawMaterialCard* card = new RawMaterialCard(name, age, resource, quantity);
    card->setCost(cost);
    card->setChainSymbol(chainSymbol);
    card->setChainedFrom(chainedFrom);
    return card;
}

std::string RawMaterialCard::getDescription() const {
    std::stringstream ss;
    ss << Card::getDescription();
    ss << " - 生产: " << quantity << resourceTypeToString(resource);
    return ss.str();
}

// ==================== ManufacturedGoodCard ====================
ManufacturedGoodCard::ManufacturedGoodCard(const std::string& name, int age, ResourceType resource, int quantity)
    : Card(name, CardType::MANUFACTURED_GOOD, age), resource(resource), quantity(quantity) {}

void ManufacturedGoodCard::apply(Player* player, Player* opponent, GameBoard* board) {
    // 制成品卡不需要特殊应用逻辑
}

int ManufacturedGoodCard::getVictoryPoints(Player* player, Player* opponent) const {
    return 0;
}

Card* ManufacturedGoodCard::clone() const {
    ManufacturedGoodCard* card = new ManufacturedGoodCard(name, age, resource, quantity);
    card->setCost(cost);
    card->setChainSymbol(chainSymbol);
    card->setChainedFrom(chainedFrom);
    return card;
}

std::string ManufacturedGoodCard::getDescription() const {
    std::stringstream ss;
    ss << Card::getDescription();
    ss << " - 生产: " << quantity << resourceTypeToString(resource);
    return ss.str();
}

// ==================== CivilianCard ====================
CivilianCard::CivilianCard(const std::string& name, int age, int victoryPoints)
    : Card(name, CardType::CIVILIAN, age), victoryPoints(victoryPoints) {}

void CivilianCard::apply(Player* player, Player* opponent, GameBoard* board) {
    // 平民建筑不需要特殊应用逻辑,点数在计算时累加
}

int CivilianCard::getVictoryPoints(Player* player, Player* opponent) const {
    return victoryPoints;
}

Card* CivilianCard::clone() const {
    CivilianCard* card = new CivilianCard(name, age, victoryPoints);
    card->setCost(cost);
    card->setChainSymbol(chainSymbol);
    card->setChainedFrom(chainedFrom);
    return card;
}

std::string CivilianCard::getDescription() const {
    std::stringstream ss;
    ss << Card::getDescription();
    ss << " - 胜利点数: " << victoryPoints;
    return ss.str();
}

// ==================== ScientificCard ====================
ScientificCard::ScientificCard(const std::string& name, int age, ScientificSymbol symbol, int victoryPoints)
    : Card(name, CardType::SCIENTIFIC, age), symbol(symbol), victoryPoints(victoryPoints) {}

void ScientificCard::apply(Player* player, Player* opponent, GameBoard* board) {
    player->addScientificSymbol(symbol);
}

int ScientificCard::getVictoryPoints(Player* player, Player* opponent) const {
    return victoryPoints;
}

Card* ScientificCard::clone() const {
    ScientificCard* card = new ScientificCard(name, age, symbol, victoryPoints);
    card->setCost(cost);
    card->setChainSymbol(chainSymbol);
    card->setChainedFrom(chainedFrom);
    return card;
}

std::string ScientificCard::getDescription() const {
    std::stringstream ss;
    ss << Card::getDescription();
    ss << " - 科学符号: " << scientificSymbolToString(symbol);
    ss << ", 胜利点数: " << victoryPoints;
    return ss.str();
}

// ==================== MilitaryCard ====================
MilitaryCard::MilitaryCard(const std::string& name, int age, int militaryPower)
    : Card(name, CardType::MILITARY, age), militaryPower(militaryPower) {}

void MilitaryCard::apply(Player* player, Player* opponent, GameBoard* board) {
    player->addMilitaryPower(militaryPower);
    // 军事轨道的移动由Game类处理
}

int MilitaryCard::getVictoryPoints(Player* player, Player* opponent) const {
    return 0;  // 军事卡不直接提供点数,通过军事优势获得
}

Card* MilitaryCard::clone() const {
    MilitaryCard* card = new MilitaryCard(name, age, militaryPower);
    card->setCost(cost);
    card->setChainSymbol(chainSymbol);
    card->setChainedFrom(chainedFrom);
    return card;
}

std::string MilitaryCard::getDescription() const {
    std::stringstream ss;
    ss << Card::getDescription();
    ss << " - 军事力量: " << militaryPower << "盾";
    return ss.str();
}

// ==================== CommercialCard ====================
CommercialCard::CommercialCard(const std::string& name, int age, CommercialEffect effect)
    : Card(name, CardType::COMMERCIAL, age), effect(effect), 
      victoryPoints(0), immediateCoins(0), coinsPerCard(0), 
      countedCardType(CardType::RAW_MATERIAL) {}

void CommercialCard::apply(Player* player, Player* opponent, GameBoard* board) {
    switch (effect) {
        case CommercialEffect::COINS:
            player->addCoins(immediateCoins);
            break;
            
        case CommercialEffect::REDUCE_RAW_COST:
            player->setRawMaterialDiscount(1);
            break;
            
        case CommercialEffect::REDUCE_MANUFACTURED_COST:
            player->setManufacturedGoodDiscount(1);
            break;
            
        case CommercialEffect::COINS_PER_CARD: {
            int count = player->countCardsByType(countedCardType);
            player->addCoins(count * coinsPerCard);
            break;
        }
            
        default:
            break;
    }
}

int CommercialCard::getVictoryPoints(Player* player, Player* opponent) const {
    int points = victoryPoints;
    
    if (effect == CommercialEffect::COINS_PER_CARD) {
        // 某些商业卡在游戏结束时也提供点数
        // 这里简化处理
    }
    
    return points;
}

Card* CommercialCard::clone() const {
    CommercialCard* card = new CommercialCard(name, age, effect);
    card->setCost(cost);
    card->setChainSymbol(chainSymbol);
    card->setChainedFrom(chainedFrom);
    card->victoryPoints = victoryPoints;
    card->immediateCoins = immediateCoins;
    card->producedResource = producedResource;
    card->coinsPerCard = coinsPerCard;
    card->countedCardType = countedCardType;
    return card;
}

std::string CommercialCard::getDescription() const {
    std::stringstream ss;
    ss << Card::getDescription();
    
    switch (effect) {
        case CommercialEffect::COINS:
            ss << " - 立即获得: " << immediateCoins << "金币";
            break;
        case CommercialEffect::REDUCE_RAW_COST:
            ss << " - 效果: 购买原材料减1金币";
            break;
        case CommercialEffect::REDUCE_MANUFACTURED_COST:
            ss << " - 效果: 购买制成品减1金币";
            break;
        case CommercialEffect::COINS_PER_CARD:
            ss << " - 效果: 每张" << cardTypeToString(countedCardType) << coinsPerCard << "金币";
            break;
        default:
            break;
    }
    
    if (victoryPoints > 0) {
        ss << ", 胜利点数: " << victoryPoints;
    }
    
    return ss.str();
}

// ==================== GuildCard ====================
GuildCard::GuildCard(const std::string& name, GuildType guildType, int pointsPerCard)
    : Card(name, CardType::GUILD, 3), guildType(guildType), pointsPerCard(pointsPerCard) {}

void GuildCard::apply(Player* player, Player* opponent, GameBoard* board) {
    // 公会卡不需要立即应用,效果在计算点数时生效
}

int GuildCard::getVictoryPoints(Player* player, Player* opponent) const {
    return calculateGuildPoints(player, opponent);
}

Card* GuildCard::clone() const {
    GuildCard* card = new GuildCard(name, guildType, pointsPerCard);
    card->setCost(cost);
    return card;
}

int GuildCard::calculateGuildPoints(Player* player, Player* opponent) const {
    int count = 0;
    
    switch (guildType) {
        case GuildType::BUILDERS:
            // 每个奇迹2点
            count = player->getWonders().size() + opponent->getWonders().size();
            return count * 2;
            
        case GuildType::TRADERS:
            // 每个黄色卡1点
            count = player->countCardsByType(CardType::COMMERCIAL);
            count += opponent->countCardsByType(CardType::COMMERCIAL);
            return count;
            
        case GuildType::MAGISTRATES:
            // 每个蓝色卡1点
            count = player->countCardsByType(CardType::CIVILIAN);
            count += opponent->countCardsByType(CardType::CIVILIAN);
            return count;
            
        case GuildType::SCIENTISTS:
            // 每个绿色卡1点
            count = player->countCardsByType(CardType::SCIENTIFIC);
            count += opponent->countCardsByType(CardType::SCIENTIFIC);
            return count;
            
        case GuildType::SHIPOWNERS:
            // 每个棕色+灰色卡1点
            count = player->countCardsByType(CardType::RAW_MATERIAL);
            count += player->countCardsByType(CardType::MANUFACTURED_GOOD);
            count += opponent->countCardsByType(CardType::RAW_MATERIAL);
            count += opponent->countCardsByType(CardType::MANUFACTURED_GOOD);
            return count;
            
        case GuildType::TACTICIANS:
            // 每个红色卡1点
            count = player->countCardsByType(CardType::MILITARY);
            count += opponent->countCardsByType(CardType::MILITARY);
            return count;
            
        case GuildType::MONEYLENDERS:
            // 每3金币1点(双方)
            return (player->getCoins() + opponent->getCoins()) / 3;
            
        default:
            return 0;
    }
}

std::string GuildCard::getDescription() const {
    std::stringstream ss;
    ss << Card::getDescription();
    ss << " - " << guildTypeToString(guildType);
    return ss.str();
}
