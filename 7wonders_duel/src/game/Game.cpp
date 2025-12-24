#include "../../include/game/Game.h"
#include "../../include/player/Player.h"
#include "../../include/player/HumanPlayer.h"
#include "../../include/player/PlayerStrategy.h"
#include "../../include/cards/CardFactory.h"
#include "../../include/ui/ConsoleDisplay.h"
#include "../../include/ui/InputHandler.h"
#include <iostream>
#include <algorithm>
#include <random>

Game::Game() : currentAge(1), gameOver(false), winner(nullptr) {
    board = new GameBoard();
    victoryChecker = new VictoryCondition();
    display = new ConsoleDisplay();
    inputHandler = new InputHandler();
    player1 = nullptr;
    player2 = nullptr;
    currentPlayer = nullptr;
}

Game::~Game() {
    delete board;
    delete victoryChecker;
    delete display;
    delete inputHandler;
    delete player1;
    delete player2;
    
    cleanupCards();
}

void Game::cleanupCards() {
    // 清理所有卡牌
    for (auto* card : allCards) {
        delete card;
    }
    allCards.clear();
    
    // 清理所有奇迹卡
    for (auto* wonder : allWonders) {
        delete wonder;
    }
    allWonders.clear();
}

void Game::initialize() {
    std::cout << "=== 7 Wonders Duel ===" << std::endl;
    std::cout << "欢迎来到七大奇迹:对决!" << std::endl << std::endl;
    
    board->initialize();
    setupPlayers();
    setupWonders();
    
    // 决定起始玩家
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    currentPlayer = (dis(gen) == 0) ? player1 : player2;
    
    std::cout << "\n起始玩家: " << currentPlayer->getName() << std::endl;
}

void Game::setupPlayers() {
    std::cout << "\n=== 玩家设置 ===" << std::endl;
    
    // 玩家1
    std::cout << "玩家1名称: ";
    std::string name1;
    std::getline(std::cin, name1);
    if (name1.empty()) name1 = "玩家1";
    
    std::cout << "玩家1类型 (1=人类, 2=随机AI, 3=贪心AI): ";
    int type1 = inputHandler->getIntInput("", 1, 3);
    
    if (type1 == 1) {
        player1 = new HumanPlayer(name1);
    } else if (type1 == 2) {
        player1 = new AIPlayer(name1, new RandomAI());
    } else {
        player1 = new AIPlayer(name1, new GreedyAI());
    }
    
    // 玩家2
    std::cout << "\n玩家2名称: ";
    std::string name2;
    std::getline(std::cin, name2);
    if (name2.empty()) name2 = "玩家2";
    
    std::cout << "玩家2类型 (1=人类, 2=随机AI, 3=贪心AI): ";
    int type2 = inputHandler->getIntInput("", 1, 3);
    
    if (type2 == 1) {
        player2 = new HumanPlayer(name2);
    } else if (type2 == 2) {
        player2 = new AIPlayer(name2, new RandomAI());
    } else {
        player2 = new AIPlayer(name2, new GreedyAI());
    }
    
    std::cout << "\n玩家设置完成!" << std::endl;
}

void Game::setupWonders() {
    std::cout << "\n=== 奇迹选择 ===" << std::endl;
    
    // 创建所有奇迹卡
    allWonders = CardFactory::createAllWonderCards();
    
    // 打乱奇迹卡
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allWonders.begin(), allWonders.end(), g);
    
    // 每个玩家选择4张奇迹
    std::vector<WonderCard*> pool;
    for (int i = 0; i < 8 && i < allWonders.size(); i++) {
        pool.push_back(allWonders[i]);
    }
    
    // 简化:随机分配奇迹
    for (int i = 0; i < 4; i++) {
        player1->addAvailableWonder(pool[i]);
    }
    for (int i = 4; i < 8; i++) {
        player2->addAvailableWonder(pool[i]);
    }
    
    std::cout << player1->getName() << " 的奇迹: ";
    for (auto* w : player1->getAvailableWonders()) {
        std::cout << w->getName() << " ";
    }
    std::cout << std::endl;
    
    std::cout << player2->getName() << " 的奇迹: ";
    for (auto* w : player2->getAvailableWonders()) {
        std::cout << w->getName() << " ";
    }
    std::cout << std::endl;
}

void Game::startGame() {
    initialize();
    
    for (currentAge = 1; currentAge <= 3 && !gameOver; currentAge++) {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "=== 时代 " << currentAge << " 开始 ===" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        playAge(currentAge);
        
        if (checkVictory()) {
            break;
        }
    }
    
    if (!gameOver) {
        // 游戏结束,计算平民胜利
        winner = victoryChecker->calculateCivilianVictory(player1, player2);
        victoryType = VictoryType::CIVILIAN;
        gameOver = true;
    }
    
    endGame();
}

void Game::playAge(int age) {
    // 创建该时代的卡牌组
    std::vector<Card*> ageCards;
    
    switch (age) {
        case 1:
            ageCards = CardFactory::createAgeIDeck();
            break;
        case 2:
            ageCards = CardFactory::createAgeIIDeck();
            break;
        case 3: {
            ageCards = CardFactory::createAgeIIIDeck();
            // 添加3张随机公会卡
            auto guilds = CardFactory::createAllGuildCards();
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(guilds.begin(), guilds.end(), g);
            for (int i = 0; i < 3 && i < guilds.size(); i++) {
                ageCards.push_back(guilds[i]);
            }
            // 删除未使用的公会卡
            for (size_t i = 3; i < guilds.size(); i++) {
                delete guilds[i];
            }
            break;
        }
    }
    
    // 保存卡牌指针用于后续清理
    allCards.insert(allCards.end(), ageCards.begin(), ageCards.end());
    
    // 设置金字塔
    board->setupAge(age, ageCards);
    
    // 玩家轮流行动直到金字塔为空
    while (!board->isAgeComplete() && !gameOver) {
        playTurn();
        
        if (checkVictory()) {
            break;
        }
        
        switchPlayer();
    }
}

void Game::playTurn() {
    Player* opponent = getOpponent();
    
    std::cout << "\n" << std::string(40, '-') << std::endl;
    std::cout << "当前玩家: " << currentPlayer->getName() << std::endl;
    
    // 显示游戏状态
    display->displayGameState(board, currentPlayer, opponent);
    
    // 获取可用卡牌
    std::vector<Card*> availableCards = board->getAccessibleCards();
    
    if (availableCards.empty()) {
        std::cout << "没有可用卡牌!" << std::endl;
        return;
    }
    
    // 构建游戏状态
    GameState state;
    state.currentPlayer = currentPlayer;
    state.opponent = opponent;
    state.board = board;
    state.availableCards = availableCards;
    state.currentAge = currentAge;
    state.discardPile = discardPile;
    
    // 获取玩家决策
    Action* action = nullptr;
    
    // 检查玩家类型
    HumanPlayer* humanPlayer = dynamic_cast<HumanPlayer*>(currentPlayer);
    if (humanPlayer) {
        // 人类玩家,通过UI获取行动
        action = inputHandler->getPlayerAction(currentPlayer, opponent, availableCards, board);
    } else {
        // AI玩家
        action = currentPlayer->makeDecision(state);
        
        if (action) {
            std::cout << "\nAI选择: ";
            switch (action->type) {
                case ActionType::BUILD_STRUCTURE:
                    std::cout << "建造 " << action->targetCard->getName();
                    break;
                case ActionType::BUILD_WONDER:
                    std::cout << "建造奇迹 " << action->targetWonder->getName();
                    break;
                case ActionType::DISCARD_FOR_COINS:
                    std::cout << "弃牌换金币";
                    break;
            }
            std::cout << std::endl;
        }
    }
    
    if (action) {
        executeAction(action, currentPlayer);
        delete action;
    }
}

// 继续在下一个文件...

bool Game::executeAction(Action* action, Player* player) {
    Player* opponent = getOpponent();
    
    switch (action->type) {
        case ActionType::BUILD_STRUCTURE: {
            Card* card = action->targetCard;
            
            // 检查是否可以免费建造
            bool isFree = card->hasFreeConstruction(player);
            
            // 计算成本
            int cost = 0;
            if (!isFree) {
                cost = player->calculateResourceCost(card->getCost(), opponent);
            }
            
            // 支付成本
            if (!isFree && !player->removeCoins(cost)) {
                std::cout << "金币不足!" << std::endl;
                return false;
            }
            
            // 添加建筑到玩家城市
            player->addBuilding(card);
            
            // 应用卡牌效果
            card->apply(player, opponent, board);
            
            // 如果是军事卡,更新军事轨道
            if (card->getType() == CardType::MILITARY) {
                MilitaryCard* militaryCard = dynamic_cast<MilitaryCard*>(card);
                if (militaryCard) {
                    updateMilitaryTrack(militaryCard->getMilitaryPower());
                }
            }
            
            // 如果是科学卡,检查进度标记
            if (card->getType() == CardType::SCIENTIFIC) {
                checkProgressTokens(player);
            }
            
            // 从金字塔中移除卡牌
            board->removeCard(card);
            
            std::cout << player->getName() << " 建造了 " << card->getName() << std::endl;
            if (!isFree && cost > 0) {
                std::cout << "花费: " << cost << "金币" << std::endl;
            }
            
            break;
        }
        
        case ActionType::BUILD_WONDER: {
            WonderCard* wonder = action->targetWonder;
            Card* usedCard = action->targetCard;
            
            // 计算成本
            int cost = player->calculateResourceCost(wonder->getCost(), opponent);
            
            // 支付成本
            if (!player->removeCoins(cost)) {
                std::cout << "金币不足!" << std::endl;
                return false;
            }
            
            // 建造奇迹
            player->buildWonder(wonder, usedCard);
            
            // 应用奇迹效果
            wonder->apply(player, opponent, board);
            
            // 从金字塔中移除使用的卡牌
            board->removeCard(usedCard);
            
            // 将使用的卡牌放入弃牌堆
            discardPile.push_back(usedCard);
            
            std::cout << player->getName() << " 建造了奇迹 " << wonder->getName() << std::endl;
            std::cout << "花费: " << cost << "金币" << std::endl;
            
            // 检查是否有再行动效果
            if (wonder->hasReplayEffect()) {
                std::cout << "获得再行动一次的机会!" << std::endl;
                // 不切换玩家
                return true;
            }
            
            break;
        }
        
        case ActionType::DISCARD_FOR_COINS: {
            Card* card = action->targetCard;
            
            // 获得金币: 2 + 对手黄色卡数量
            int coins = 2 + opponent->countCardsByType(CardType::COMMERCIAL);
            player->addCoins(coins);
            
            // 从金字塔中移除卡牌
            board->removeCard(card);
            
            // 放入弃牌堆
            discardPile.push_back(card);
            
            std::cout << player->getName() << " 弃牌换取 " << coins << "金币" << std::endl;
            
            break;
        }
    }
    
    return true;
}

void Game::updateMilitaryTrack(int militaryPowerChange) {
    Player* opponent = getOpponent();
    
    // 计算军事力量差
    int powerDiff = currentPlayer->getMilitaryPower() - opponent->getMilitaryPower();
    
    // 移动冲突棋子
    int oldPosition = board->getMilitaryTrack()->getPosition();
    board->getMilitaryTrack()->moveConflictPawn(militaryPowerChange, currentPlayer, opponent);
    int newPosition = board->getMilitaryTrack()->getPosition();
    
    if (newPosition != oldPosition) {
        std::cout << "军事轨道移动: " << oldPosition << " -> " << newPosition << std::endl;
    }
}

void Game::checkProgressTokens(Player* player) {
    // 检查是否有相同的科学符号对
    const auto& symbols = player->getScientificSymbols();
    
    for (const auto& pair : symbols) {
        if (pair.second >= 2) {
            // 有一对相同符号,可以获得进度标记
            auto& availableTokens = board->getAvailableProgressTokens();
            
            if (!availableTokens.empty()) {
                std::cout << "\n获得相同科学符号对!可以选择一个进度标记:" << std::endl;
                
                for (size_t i = 0; i < availableTokens.size(); i++) {
                    std::cout << (i + 1) << ". " << availableTokens[i]->getDescription() << std::endl;
                }
                
                int choice = inputHandler->getIntInput("选择进度标记", 1, availableTokens.size());
                ProgressToken* token = availableTokens[choice - 1];
                
                // 应用进度标记效果
                token->apply(player);
                player->addProgressToken(token);
                
                // 从可用列表中移除
                board->removeProgressToken(token);
                
                std::cout << player->getName() << " 获得了进度标记: " << token->getName() << std::endl;
                
                // 检查是否有再行动效果(神学)
                if (token->getType() == ProgressType::THEOLOGY) {
                    std::cout << "获得再行动一次的机会!" << std::endl;
                }
            }
            
            // 只处理一次
            break;
        }
    }
}

bool Game::checkVictory() {
    // 检查军事胜利
    if (victoryChecker->checkMilitaryVictory(board->getMilitaryTrack())) {
        int position = board->getMilitaryTrack()->getPosition();
        if (position == 9) {
            winner = player1;
        } else {
            winner = player2;
        }
        victoryType = VictoryType::MILITARY;
        gameOver = true;
        return true;
    }
    
    // 检查科学胜利
    if (victoryChecker->checkScientificVictory(player1)) {
        winner = player1;
        victoryType = VictoryType::SCIENTIFIC;
        gameOver = true;
        return true;
    }
    
    if (victoryChecker->checkScientificVictory(player2)) {
        winner = player2;
        victoryType = VictoryType::SCIENTIFIC;
        gameOver = true;
        return true;
    }
    
    return false;
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

Player* Game::getOpponent() {
    return (currentPlayer == player1) ? player2 : player1;
}

void Game::endGame() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "=== 游戏结束 ===" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    if (winner) {
        std::cout << "\n胜利者: " << winner->getName() << std::endl;
        
        switch (victoryType) {
            case VictoryType::MILITARY:
                std::cout << "胜利方式: 军事胜利!" << std::endl;
                break;
            case VictoryType::SCIENTIFIC:
                std::cout << "胜利方式: 科学胜利!" << std::endl;
                break;
            case VictoryType::CIVILIAN:
                std::cout << "胜利方式: 平民胜利!" << std::endl;
                break;
        }
    } else {
        std::cout << "\n游戏平局!" << std::endl;
    }
    
    // 显示最终分数
    std::cout << "\n最终分数:" << std::endl;
    int p1Score = victoryChecker->calculateTotalPoints(player1, player2);
    int p2Score = victoryChecker->calculateTotalPoints(player2, player1);
    
    std::cout << player1->getName() << ": " << p1Score << "点" << std::endl;
    std::cout << player2->getName() << ": " << p2Score << "点" << std::endl;
    
    // 显示详细信息
    display->displayFinalScores(player1, player2, board);
}
