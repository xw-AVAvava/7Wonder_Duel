#ifndef TYPES_H
#define TYPES_H

#include <string>

// 资源类型
enum class ResourceType {
    WOOD,
    STONE,
    CLAY,
    GLASS,
    PAPYRUS
};

// 科学符号
enum class ScientificSymbol {
    WHEEL,      // 轮子
    COMPASS,    // 罗盘
    TABLET,     // 石板
    SUNDIAL,    // 日晷
    MORTAR,     // 研钵
    SCALES,     // 天平
    ARMILLARY   // 浑天仪
};

// 卡牌类型
enum class CardType {
    RAW_MATERIAL,      // 原材料(棕色)
    MANUFACTURED_GOOD, // 制成品(灰色)
    CIVILIAN,          // 平民建筑(蓝色)
    SCIENTIFIC,        // 科学建筑(绿色)
    COMMERCIAL,        // 商业建筑(黄色)
    MILITARY,          // 军事建筑(红色)
    GUILD              // 公会(紫色)
};

// 玩家行动类型
enum class ActionType {
    BUILD_STRUCTURE,    // 建造建筑
    BUILD_WONDER,       // 建造奇迹
    DISCARD_FOR_COINS   // 弃牌换金币
};

// 胜利类型
enum class VictoryType {
    MILITARY,   // 军事胜利
    SCIENTIFIC, // 科学胜利
    CIVILIAN    // 平民胜利
};

// 进度标记类型
enum class ProgressType {
    AGRICULTURE,    // 农业
    ARCHITECTURE,   // 建筑学
    ECONOMY,        // 经济
    LAW,            // 法律
    MASONRY,        // 石工术
    MATHEMATICS,    // 数学
    PHILOSOPHY,     // 哲学
    STRATEGY,       // 策略
    THEOLOGY,       // 神学
    URBANISM        // 城市规划
};

// 公会类型
enum class GuildType {
    BUILDERS,       // 建筑师公会
    TRADERS,        // 商人公会
    MAGISTRATES,    // 治安官公会
    SCIENTISTS,     // 科学家公会
    SHIPOWNERS,     // 船主公会
    TACTICIANS,     // 战术家公会
    MONEYLENDERS    // 放贷者公会
};

// 商业效果类型
enum class CommercialEffect {
    NONE,
    COINS,                      // 直接给金币
    RESOURCE_PRODUCTION,        // 生产资源
    REDUCE_RAW_COST,           // 降低原材料购买成本
    REDUCE_MANUFACTURED_COST,  // 降低制成品购买成本
    COINS_PER_CARD             // 每张特定卡牌给金币
};

// 奇迹效果类型
enum class WonderEffect {
    NONE,
    VICTORY_POINTS,         // 胜利点数
    REPLAY,                 // 再行动一次
    COINS,                  // 金币
    MILITARY,               // 军事力量
    PROGRESS_TOKEN,         // 进度标记
    DESTROY_CARD,           // 摧毁对手卡牌
    RECYCLE_CARD,           // 从弃牌堆回收
    REDUCE_TRADE_COST,      // 降低交易成本
    OPPONENT_LOSE_COINS,    // 对手失去金币
    MILITARY_TOKENS_BONUS   // 军事标记额外奖励
};

// 辅助函数:将枚举转换为字符串
std::string resourceTypeToString(ResourceType type);
std::string scientificSymbolToString(ScientificSymbol symbol);
std::string cardTypeToString(CardType type);
std::string progressTypeToString(ProgressType type);
std::string guildTypeToString(GuildType type);

#endif // TYPES_H
