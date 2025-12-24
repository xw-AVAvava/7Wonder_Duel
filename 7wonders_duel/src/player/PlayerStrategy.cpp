#include "../../include/player/PlayerStrategy.h"
#include "../../include/player/Player.h"
#include "../../include/cards/Card.h"
#include "../../include/cards/AllCards.h"
#include "../../include/cards/WonderCard.h"
#include "../../include/game/GameBoard.h"
#include <random>
#include <algorithm>
#include <iostream>

// ==================== HumanStrategy ====================
Action* HumanStrategy::chooseAction(GameState& state) {
    // 这个方法将由UI层调用,返回用户选择的行动
    // 实际实现在UI部分
    return nullptr;
}

// ==================== AIStrategy ====================
double AIStrategy::evaluateCard(Card* card, GameState& state) {
    double value = 0.0;
    
    // 基于卡牌类型评估
    switch (card->getType()) {
        case CardType::CIVILIAN:
            value = card->getVictoryPoints(state.currentPlayer, state.opponent) * 2.0;
            break;
            
        case CardType::SCIENTIFIC:
            value = 15.0;  // 科学卡很有价值
            if (state.currentPlayer->getScientificSymbols().size() >= 5) {
                value = 30.0;  // 接近科学胜利时更有价值
            }
            break;
            
        case CardType::MILITARY:
            value = 10.0;
            break;
            
        case CardType::COMMERCIAL:
            value = 8.0;
            break;
            
        case CardType::RAW_MATERIAL:
        case CardType::MANUFACTURED_GOOD:
            value = 5.0;
            if (state.currentAge >= 2) value = 3.0;  // 后期资源卡价值降低
            break;
            
        case CardType::GUILD:
            value = 20.0;
            break;
    }
    
    return value;
}

double AIStrategy::evaluateBuildAction(Card* card, GameState& state) {
    double value = evaluateCard(card, state);
    
    // 考虑成本
    int cost = state.currentPlayer->calculateResourceCost(card->getCost(), state.opponent);
    if (cost > state.currentPlayer->getCoins()) {
        return -1000.0;  // 买不起
    }
    
    // 免费建造额外奖励
    if (card->hasFreeConstruction(state.currentPlayer)) {
        value += 10.0;
    }
    
    // 成本越低越好
    value -= cost * 0.5;
    
    return value;
}

double AIStrategy::evaluateWonderAction(WonderCard* wonder, GameState& state) {
    if (wonder->isBuilt()) {
        return -1000.0;
    }
    
    double value = wonder->getVictoryPoints(state.currentPlayer, state.opponent) * 1.5;
    
    // 考虑特殊效果
    if (wonder->hasReplayEffect()) {
        value += 15.0;
    }
    
    int cost = state.currentPlayer->calculateResourceCost(wonder->getCost(), state.opponent);
    if (cost > state.currentPlayer->getCoins()) {
        return -1000.0;
    }
    
    value -= cost * 0.5;
    
    return value;
}

// ==================== RandomAI ====================
Action* RandomAI::chooseAction(GameState& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::vector<Action*> possibleActions;
    
    // 收集所有可能的行动
    for (auto* card : state.availableCards) {
        // 建造建筑
        if (state.currentPlayer->canAfford(card->getCost(), state.opponent) ||
            card->hasFreeConstruction(state.currentPlayer)) {
            possibleActions.push_back(new Action(ActionType::BUILD_STRUCTURE, card));
        }
        
        // 建造奇迹
        WonderCard* wonder = state.currentPlayer->getUnbuiltWonder();
        if (wonder && state.currentPlayer->canAfford(wonder->getCost(), state.opponent)) {
            possibleActions.push_back(new Action(ActionType::BUILD_WONDER, card, wonder));
        }
        
        // 弃牌换金币(总是可以)
        possibleActions.push_back(new Action(ActionType::DISCARD_FOR_COINS, card));
    }
    
    if (possibleActions.empty()) {
        return nullptr;
    }
    
    // 随机选择一个行动
    std::uniform_int_distribution<> dis(0, possibleActions.size() - 1);
    int choice = dis(gen);
    
    Action* chosenAction = possibleActions[choice];
    
    // 删除未选择的行动
    for (size_t i = 0; i < possibleActions.size(); i++) {
        if (i != choice) {
            delete possibleActions[i];
        }
    }
    
    return chosenAction;
}

// ==================== GreedyAI ====================
Action* GreedyAI::chooseAction(GameState& state) {
    Action* bestAction = nullptr;
    double bestValue = -10000.0;
    
    for (auto* card : state.availableCards) {
        // 评估建造建筑
        if (state.currentPlayer->canAfford(card->getCost(), state.opponent) ||
            card->hasFreeConstruction(state.currentPlayer)) {
            double value = evaluateBuildAction(card, state);
            if (value > bestValue) {
                bestValue = value;
                if (bestAction) delete bestAction;
                bestAction = new Action(ActionType::BUILD_STRUCTURE, card);
            }
        }
        
        // 评估建造奇迹
        WonderCard* wonder = state.currentPlayer->getUnbuiltWonder();
        if (wonder && state.currentPlayer->canAfford(wonder->getCost(), state.opponent)) {
            double value = evaluateWonderAction(wonder, state);
            if (value > bestValue) {
                bestValue = value;
                if (bestAction) delete bestAction;
                bestAction = new Action(ActionType::BUILD_WONDER, card, wonder);
            }
        }
        
        // 评估弃牌换金币
        double discardValue = 2.0 + state.opponent->countCardsByType(CardType::COMMERCIAL);
        // 如果金币很少,弃牌换金币更有价值
        if (state.currentPlayer->getCoins() < 5) {
            discardValue += 5.0;
        }
        
        if (discardValue > bestValue) {
            bestValue = discardValue;
            if (bestAction) delete bestAction;
            bestAction = new Action(ActionType::DISCARD_FOR_COINS, card);
        }
    }
    
    return bestAction;
}

double GreedyAI::calculateCardValue(Card* card, GameState& state) {
    return evaluateBuildAction(card, state);
}
