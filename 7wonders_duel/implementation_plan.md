# 7 Wonders Duel 项目实施计划

## 项目架构设计

### 核心设计原则
1. **可扩展性**: 使用设计模式确保未来可以轻松添加新AI和扩展包
2. **模块化**: 将游戏逻辑、UI、AI分离
3. **面向对象**: 充分利用继承、多态和封装

### 推荐设计模式

#### 1. Strategy Pattern (策略模式)
- **用途**: 实现不同的AI玩家类型
- **实现**: 创建`PlayerStrategy`基类,派生`HumanStrategy`和`AIStrategy`
- **优势**: 便于添加新的AI策略而不修改现有代码

#### 2. Factory Pattern (工厂模式)
- **用途**: 创建不同类型的卡牌和玩家
- **实现**: `CardFactory`用于创建各种建筑卡,`PlayerFactory`用于创建玩家
- **优势**: 集中管理对象创建,便于扩展

#### 3. Observer Pattern (观察者模式)
- **用途**: 游戏状态变化通知
- **实现**: 当游戏状态改变时通知UI更新
- **优势**: 解耦游戏逻辑和显示逻辑

#### 4. Template Method Pattern (模板方法模式)
- **用途**: 定义游戏回合的基本流程
- **实现**: 在基类中定义回合结构,子类实现具体步骤
- **优势**: 保证游戏流程一致性

#### 5. Composite Pattern (组合模式)
- **用途**: 管理玩家的建筑集合
- **实现**: 将单个建筑和建筑集合统一处理
- **优势**: 简化资源计算和效果应用

## 类设计架构

### 核心类层次

```
Game (游戏管理器)
├── GameBoard (游戏板)
│   ├── MilitaryTrack (军事轨道)
│   └── CardStructure (卡牌结构 - 金字塔)
├── Player (玩家基类)
│   ├── HumanPlayer (人类玩家)
│   └── AIPlayer (AI玩家)
├── PlayerStrategy (玩家策略接口)
│   ├── HumanStrategy (人类策略)
│   └── AIStrategy (AI策略基类)
│       ├── RandomAI (随机AI)
│       └── GreedyAI (贪心AI)
├── Card (卡牌基类)
│   ├── BuildingCard (建筑卡)
│   │   ├── RawMaterialCard (原材料)
│   │   ├── ManufacturedGoodCard (制成品)
│   │   ├── CivilianCard (平民建筑)
│   │   ├── ScientificCard (科学建筑)
│   │   ├── CommercialCard (商业建筑)
│   │   ├── MilitaryCard (军事建筑)
│   │   └── GuildCard (公会)
│   └── WonderCard (奇迹卡)
├── Resource (资源系统)
│   ├── ResourceType (资源类型枚举)
│   └── ResourceManager (资源管理器)
├── Effect (效果系统)
│   └── EffectApplier (效果应用器)
├── VictoryCondition (胜利条件检查器)
└── UI (用户界面)
    ├── ConsoleDisplay (控制台显示)
    └── InputHandler (输入处理)
```

## 详细类设计

### 1. Game类
```cpp
class Game {
private:
    GameBoard* board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    int currentAge;
    VictoryCondition* victoryChecker;
    
public:
    void initialize();
    void startGame();
    void playAge(int age);
    void playTurn();
    bool checkVictory();
    void endGame();
};
```

### 2. Player类 (使用Strategy模式)
```cpp
class Player {
protected:
    string name;
    PlayerStrategy* strategy;
    vector<Card*> buildings;
    vector<WonderCard*> wonders;
    int coins;
    int militaryPower;
    vector<ScientificSymbol> scientificSymbols;
    
public:
    virtual Action* makeDecision(GameState& state) = 0;
    void addBuilding(Card* card);
    void buildWonder(WonderCard* wonder);
    int calculateVictoryPoints();
    bool canAfford(Card* card);
};

class HumanPlayer : public Player {
public:
    Action* makeDecision(GameState& state) override;
};

class AIPlayer : public Player {
public:
    Action* makeDecision(GameState& state) override;
};
```

### 3. PlayerStrategy接口
```cpp
class PlayerStrategy {
public:
    virtual Action* chooseAction(GameState& state, Player* player) = 0;
    virtual ~PlayerStrategy() = default;
};

class HumanStrategy : public PlayerStrategy {
public:
    Action* chooseAction(GameState& state, Player* player) override;
};

class AIStrategy : public PlayerStrategy {
public:
    virtual Action* chooseAction(GameState& state, Player* player) = 0;
};

class RandomAI : public AIStrategy {
public:
    Action* chooseAction(GameState& state, Player* player) override;
};

class GreedyAI : public AIStrategy {
public:
    Action* chooseAction(GameState& state, Player* player) override;
};
```

### 4. Card类层次 (使用Factory模式创建)
```cpp
class Card {
protected:
    string name;
    CardType type;
    Cost cost;
    Effect* effect;
    
public:
    virtual void apply(Player* player) = 0;
    virtual int getVictoryPoints() = 0;
    Cost getCost() const;
    virtual ~Card() = default;
};

class BuildingCard : public Card {
protected:
    string chainSymbol;
    
public:
    bool hasFreeConstruction(Player* player);
};

class MilitaryCard : public BuildingCard {
private:
    int militaryStrength;
    
public:
    void apply(Player* player) override;
    int getVictoryPoints() override;
};

class ScientificCard : public BuildingCard {
private:
    ScientificSymbol symbol;
    int victoryPoints;
    
public:
    void apply(Player* player) override;
    ScientificSymbol getSymbol() const;
};
```

### 5. CardFactory (工厂模式)
```cpp
class CardFactory {
public:
    static Card* createCard(CardData& data);
    static vector<Card*> createAgeIDeck();
    static vector<Card*> createAgeIIDeck();
    static vector<Card*> createAgeIIIDeck();
};
```

### 6. GameBoard类
```cpp
class GameBoard {
private:
    MilitaryTrack* militaryTrack;
    CardStructure* cardStructure;
    vector<ProgressToken*> availableProgressTokens;
    vector<MilitaryToken*> availableMilitaryTokens;
    
public:
    void setupAge(int age, vector<Card*>& cards);
    vector<Card*> getAvailableCards();
    void removeCard(Card* card);
    void updateMilitaryPosition(int change);
};
```

### 7. MilitaryTrack类
```cpp
class MilitaryTrack {
private:
    int conflictPawnPosition; // -9 to +9, 0 is center
    vector<MilitaryToken*> tokens;
    
public:
    void moveConflictPawn(int spaces);
    bool checkMilitaryVictory();
    MilitaryToken* getTokenAtPosition(int position);
};
```

### 8. CardStructure类 (金字塔结构)
```cpp
class CardStructure {
private:
    vector<vector<CardSlot*>> pyramid;
    
public:
    void setupPyramid(vector<Card*>& cards, int age);
    vector<Card*> getAccessibleCards();
    void removeCard(int row, int col);
    bool isAccessible(int row, int col);
};
```

### 9. VictoryCondition类
```cpp
class VictoryCondition {
public:
    bool checkMilitaryVictory(GameBoard* board);
    bool checkScientificVictory(Player* player);
    Player* calculateCivilianVictory(Player* p1, Player* p2);
};
```

### 10. ConsoleDisplay类
```cpp
class ConsoleDisplay {
public:
    void displayGameState(GameState& state);
    void displayPlayerInfo(Player* player);
    void displayAvailableCards(vector<Card*>& cards);
    void displayMilitaryTrack(MilitaryTrack* track);
    void displayWinner(Player* winner, VictoryType type);
    void clearScreen();
};
```

## 实现步骤

### 阶段1: 基础框架 (优先级: 高)
1. 创建基本类结构(Card, Player, Game)
2. 实现资源系统(Resource, Cost)
3. 实现简单的控制台UI
4. 创建游戏主循环

### 阶段2: 卡牌系统 (优先级: 高)
1. 实现所有卡牌类型
2. 创建CardFactory
3. 加载卡牌数据(可以硬编码或从文件读取)
4. 实现卡牌效果系统

### 阶段3: 游戏板和结构 (优先级: 高)
1. 实现GameBoard
2. 实现CardStructure(金字塔布局)
3. 实现MilitaryTrack
4. 实现进度标记和军事标记

### 阶段4: 玩家系统 (优先级: 高)
1. 实现Player基类
2. 实现HumanPlayer
3. 实现PlayerStrategy接口
4. 实现基本的RandomAI

### 阶段5: 游戏逻辑 (优先级: 高)
1. 实现回合流程
2. 实现玩家行动(建造、建奇迹、卖牌)
3. 实现资源购买系统
4. 实现链式建造

### 阶段6: 胜利条件 (优先级: 高)
1. 实现军事胜利检查
2. 实现科学胜利检查
3. 实现平民胜利计分
4. 实现游戏结束逻辑

### 阶段7: 奇迹系统 (优先级: 中)
1. 实现WonderCard类
2. 实现奇迹选择机制
3. 实现奇迹建造

### 阶段8: 高级AI (优先级: 中)
1. 实现GreedyAI(贪心策略)
2. 可选: 实现更智能的AI(评估策略)

### 阶段9: UI优化 (优先级: 低)
1. 改进控制台显示
2. 添加颜色支持(ANSI codes)
3. 优化布局和可读性

### 阶段10: 测试和调试 (优先级: 高)
1. 单元测试关键类
2. 集成测试完整游戏流程
3. 测试各种胜利条件
4. 测试AI行为

## 可扩展性设计

### 添加新AI的步骤
1. 创建新类继承`AIStrategy`
2. 实现`chooseAction`方法
3. 在`PlayerFactory`中注册新AI类型
4. 无需修改现有代码

### 添加扩展包的步骤
1. 创建新的卡牌类(如果需要新类型)
2. 在`CardFactory`中添加新卡牌
3. 如果有新机制,使用Strategy或Decorator模式扩展
4. 在Game类中添加扩展包启用选项

### 架构优势
- **Strategy模式**: AI完全独立,易于添加
- **Factory模式**: 卡牌创建集中管理
- **多态**: 所有卡牌通过基类接口操作
- **封装**: 游戏逻辑与UI分离

## 数据结构

### 资源类型
```cpp
enum class ResourceType {
    WOOD,
    STONE,
    CLAY,
    GLASS,
    PAPYRUS
};
```

### 科学符号
```cpp
enum class ScientificSymbol {
    WHEEL,
    COMPASS,
    TABLET,
    SUNDIAL,
    MORTAR,
    SCALES,
    ARMILLARY
};
```

### 卡牌类型
```cpp
enum class CardType {
    RAW_MATERIAL,
    MANUFACTURED_GOOD,
    CIVILIAN,
    SCIENTIFIC,
    COMMERCIAL,
    MILITARY,
    GUILD
};
```

### 玩家行动
```cpp
enum class ActionType {
    BUILD_STRUCTURE,
    BUILD_WONDER,
    DISCARD_FOR_COINS
};

class Action {
    ActionType type;
    Card* targetCard;
    WonderCard* targetWonder;
};
```

## 文件组织

```
project/
├── src/
│   ├── main.cpp
│   ├── game/
│   │   ├── Game.cpp
│   │   ├── GameBoard.cpp
│   │   ├── MilitaryTrack.cpp
│   │   ├── CardStructure.cpp
│   │   └── VictoryCondition.cpp
│   ├── player/
│   │   ├── Player.cpp
│   │   ├── HumanPlayer.cpp
│   │   ├── AIPlayer.cpp
│   │   └── PlayerStrategy.cpp
│   ├── cards/
│   │   ├── Card.cpp
│   │   ├── BuildingCard.cpp
│   │   ├── WonderCard.cpp
│   │   ├── MilitaryCard.cpp
│   │   ├── ScientificCard.cpp
│   │   └── CardFactory.cpp
│   ├── resources/
│   │   ├── Resource.cpp
│   │   └── ResourceManager.cpp
│   └── ui/
│       ├── ConsoleDisplay.cpp
│       └── InputHandler.cpp
├── include/
│   ├── game/
│   ├── player/
│   ├── cards/
│   ├── resources/
│   └── ui/
├── data/
│   └── cards.txt (可选: 卡牌数据文件)
└── Makefile
```

## 开发建议

### 1. 迭代开发
- 先实现最小可玩版本
- 逐步添加功能
- 每个阶段都保持代码可编译运行

### 2. 测试驱动
- 编写关键类的测试
- 测试胜利条件
- 测试资源计算

### 3. 代码质量
- 使用智能指针管理内存
- 遵循C++最佳实践
- 添加适当的注释

### 4. 版本控制
- 使用Git管理代码
- 频繁提交
- 使用分支开发新功能

## 时间估算

- 基础框架: 8-10小时
- 卡牌系统: 10-12小时
- 游戏板和结构: 6-8小时
- 玩家系统: 6-8小时
- 游戏逻辑: 10-12小时
- 胜利条件: 4-6小时
- 奇迹系统: 4-6小时
- AI实现: 6-8小时
- UI优化: 4-6小时
- 测试和调试: 8-10小时
- 文档和报告: 8-10小时

**总计**: 约74-96小时 (符合项目要求的5-6小时/周 × 8周 × 5-6人 = 200-288小时团队总时)

## 关键挑战

1. **架构设计**: 需要深入理解设计模式
2. **游戏规则复杂性**: 需要仔细实现所有规则
3. **AI实现**: 需要设计合理的决策逻辑
4. **资源管理**: 需要正确处理资源生产和购买
5. **卡牌效果**: 某些卡牌有复杂的效果需要特殊处理
