#include "../../include/cards/WonderCard.h"
#include "../../include/player/Player.h"
#include "../../include/game/GameBoard.h"
#include <sstream>

WonderCard::WonderCard(const std::string& wonderName)
    : Card(wonderName, CardType::CIVILIAN, 0), wonderName(wonderName),
      victoryPoints(0), built(false), coinsReward(0), militaryPowerBonus(0),
      allowReplay(false), destroyOpponentCard(false), recycleCard(false),
      reduceTradeCost(false), opponentCoinLoss(0) {
    // 奇迹卡的age设为0表示不属于任何时代
}

void WonderCard::apply(Player* player, Player* opponent, GameBoard* board) {
    if (built) {
        return;  // 已经建造过了
    }
    
    built = true;
    
    // 应用金币奖励
    if (coinsReward > 0) {
        player->addCoins(coinsReward);
    }
    
    // 应用军事力量
    if (militaryPowerBonus > 0) {
        player->addMilitaryPower(militaryPowerBonus);
    }
    
    // 降低交易成本
    if (reduceTradeCost) {
        player->setRawMaterialDiscount(1);
        player->setManufacturedGoodDiscount(1);
    }
    
    // 对手失去金币
    if (opponentCoinLoss > 0) {
        opponent->removeCoins(opponentCoinLoss);
    }
    
    // 其他效果(摧毁卡牌、回收卡牌、进度标记等)需要在Game类中处理
}

int WonderCard::getVictoryPoints(Player* player, Player* opponent) const {
    if (!built) {
        return 0;
    }
    return victoryPoints;
}

Card* WonderCard::clone() const {
    WonderCard* card = new WonderCard(wonderName);
    card->setCost(cost);
    card->victoryPoints = victoryPoints;
    card->effects = effects;
    card->coinsReward = coinsReward;
    card->militaryPowerBonus = militaryPowerBonus;
    card->allowReplay = allowReplay;
    card->destroyOpponentCard = destroyOpponentCard;
    card->recycleCard = recycleCard;
    card->reduceTradeCost = reduceTradeCost;
    card->opponentCoinLoss = opponentCoinLoss;
    return card;
}

void WonderCard::addEffect(WonderEffect effect) {
    effects.push_back(effect);
}

std::string WonderCard::getDescription() const {
    std::stringstream ss;
    ss << "[奇迹] " << wonderName;
    
    if (!cost.isEmpty()) {
        ss << " - 成本: " << cost.toString();
    }
    
    ss << " - 效果: ";
    
    if (victoryPoints > 0) {
        ss << victoryPoints << "点";
    }
    
    if (coinsReward > 0) {
        ss << ", " << coinsReward << "金币";
    }
    
    if (militaryPowerBonus > 0) {
        ss << ", " << militaryPowerBonus << "盾";
    }
    
    if (allowReplay) {
        ss << ", 再行动一次";
    }
    
    if (reduceTradeCost) {
        ss << ", 降低交易成本";
    }
    
    if (destroyOpponentCard) {
        ss << ", 摧毁对手卡牌";
    }
    
    if (recycleCard) {
        ss << ", 回收弃牌";
    }
    
    if (opponentCoinLoss > 0) {
        ss << ", 对手失去" << opponentCoinLoss << "金币";
    }
    
    if (built) {
        ss << " [已建造]";
    }
    
    return ss.str();
}
