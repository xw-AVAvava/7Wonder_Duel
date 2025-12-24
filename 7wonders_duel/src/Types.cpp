#include "../include/Types.h"

std::string resourceTypeToString(ResourceType type) {
    switch (type) {
        case ResourceType::WOOD: return "木材";
        case ResourceType::STONE: return "石料";
        case ResourceType::CLAY: return "黏土";
        case ResourceType::GLASS: return "玻璃";
        case ResourceType::PAPYRUS: return "纸莎草纸";
        default: return "未知";
    }
}

std::string scientificSymbolToString(ScientificSymbol symbol) {
    switch (symbol) {
        case ScientificSymbol::WHEEL: return "轮子";
        case ScientificSymbol::COMPASS: return "罗盘";
        case ScientificSymbol::TABLET: return "石板";
        case ScientificSymbol::SUNDIAL: return "日晷";
        case ScientificSymbol::MORTAR: return "研钵";
        case ScientificSymbol::SCALES: return "天平";
        case ScientificSymbol::ARMILLARY: return "浑天仪";
        default: return "未知";
    }
}

std::string cardTypeToString(CardType type) {
    switch (type) {
        case CardType::RAW_MATERIAL: return "原材料";
        case CardType::MANUFACTURED_GOOD: return "制成品";
        case CardType::CIVILIAN: return "平民建筑";
        case CardType::SCIENTIFIC: return "科学建筑";
        case CardType::COMMERCIAL: return "商业建筑";
        case CardType::MILITARY: return "军事建筑";
        case CardType::GUILD: return "公会";
        default: return "未知";
    }
}

std::string progressTypeToString(ProgressType type) {
    switch (type) {
        case ProgressType::AGRICULTURE: return "农业";
        case ProgressType::ARCHITECTURE: return "建筑学";
        case ProgressType::ECONOMY: return "经济";
        case ProgressType::LAW: return "法律";
        case ProgressType::MASONRY: return "石工术";
        case ProgressType::MATHEMATICS: return "数学";
        case ProgressType::PHILOSOPHY: return "哲学";
        case ProgressType::STRATEGY: return "策略";
        case ProgressType::THEOLOGY: return "神学";
        case ProgressType::URBANISM: return "城市规划";
        default: return "未知";
    }
}

std::string guildTypeToString(GuildType type) {
    switch (type) {
        case GuildType::BUILDERS: return "建筑师公会";
        case GuildType::TRADERS: return "商人公会";
        case GuildType::MAGISTRATES: return "治安官公会";
        case GuildType::SCIENTISTS: return "科学家公会";
        case GuildType::SHIPOWNERS: return "船主公会";
        case GuildType::TACTICIANS: return "战术家公会";
        case GuildType::MONEYLENDERS: return "放贷者公会";
        default: return "未知";
    }
}
