#include "../../include/game/CardStructure.h"
#include "../../include/cards/Card.h"
#include <algorithm>
#include <random>
#include <sstream>

CardSlot::CardSlot(Card* card, int row, int col, bool faceDown)
    : card(card), row(row), col(col), faceDown(faceDown), removed(false) {}

bool CardSlot::isAccessible(const std::vector<std::vector<CardSlot*>>& pyramid) const {
    if (removed || card == nullptr) {
        return false;
    }
    
    // 最后一行的卡牌总是可访问的
    if (row == pyramid.size() - 1) {
        return true;
    }
    
    // 检查下一行是否有卡牌覆盖
    if (row + 1 < pyramid.size()) {
        const auto& nextRow = pyramid[row + 1];
        
        // 检查正下方和右下方的位置
        bool blockedLeft = false;
        bool blockedRight = false;
        
        if (col < nextRow.size() && nextRow[col] && !nextRow[col]->isRemoved()) {
            blockedLeft = true;
        }
        
        if (col + 1 < nextRow.size() && nextRow[col + 1] && !nextRow[col + 1]->isRemoved()) {
            blockedRight = true;
        }
        
        // 只有当两个位置都没有卡牌时,当前卡牌才可访问
        return !blockedLeft && !blockedRight;
    }
    
    return true;
}

CardStructure::CardStructure() : totalRows(0) {}

CardStructure::~CardStructure() {
    clearPyramid();
}

void CardStructure::clearPyramid() {
    for (auto& row : pyramid) {
        for (auto* slot : row) {
            delete slot;
        }
    }
    pyramid.clear();
}

void CardStructure::setupPyramid(std::vector<Card*>& cards, int age) {
    clearPyramid();
    
    // 打乱卡牌顺序
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
    
    switch (age) {
        case 1:
            setupAgeIPyramid(cards);
            break;
        case 2:
            setupAgeIIPyramid(cards);
            break;
        case 3:
            setupAgeIIIPyramid(cards);
            break;
    }
}

void CardStructure::setupAgeIPyramid(std::vector<Card*>& cards) {
    // 时代I金字塔: 20张卡牌,部分面朝下
    // 行数: 1, 2, 3, 2, 4, 3, 4
    
    int cardIndex = 0;
    std::vector<int> rowSizes = {1, 2, 3, 2, 4, 3, 4};
    std::vector<bool> faceDownPattern = {
        false,              // 第1行
        true, false,        // 第2行
        false, true, false, // 第3行
        true, false,        // 第4行
        false, true, false, true, // 第5行
        false, true, false, // 第6行
        true, false, true, false  // 第7行
    };
    
    int faceDownIndex = 0;
    for (int rowSize : rowSizes) {
        std::vector<CardSlot*> row;
        for (int col = 0; col < rowSize && cardIndex < cards.size(); col++) {
            bool faceDown = faceDownPattern[faceDownIndex++];
            row.push_back(new CardSlot(cards[cardIndex++], pyramid.size(), col, faceDown));
        }
        pyramid.push_back(row);
    }
    
    totalRows = pyramid.size();
}

void CardStructure::setupAgeIIPyramid(std::vector<Card*>& cards) {
    // 时代II金字塔: 20张卡牌,类似时代I
    int cardIndex = 0;
    std::vector<int> rowSizes = {1, 2, 3, 2, 4, 3, 4};
    std::vector<bool> faceDownPattern = {
        true,               // 第1行
        false, true,        // 第2行
        true, false, true,  // 第3行
        false, true,        // 第4行
        true, false, true, false, // 第5行
        true, false, true,  // 第6行
        false, true, false, true  // 第7行
    };
    
    int faceDownIndex = 0;
    for (int rowSize : rowSizes) {
        std::vector<CardSlot*> row;
        for (int col = 0; col < rowSize && cardIndex < cards.size(); col++) {
            bool faceDown = faceDownPattern[faceDownIndex++];
            row.push_back(new CardSlot(cards[cardIndex++], pyramid.size(), col, faceDown));
        }
        pyramid.push_back(row);
    }
    
    totalRows = pyramid.size();
}

void CardStructure::setupAgeIIIPyramid(std::vector<Card*>& cards) {
    // 时代III金字塔: 20张卡牌
    // 行数: 1, 2, 3, 4, 5, 4, 1
    
    int cardIndex = 0;
    std::vector<int> rowSizes = {1, 2, 3, 4, 5, 4, 1};
    
    // 时代III所有卡牌面朝上
    for (int rowSize : rowSizes) {
        std::vector<CardSlot*> row;
        for (int col = 0; col < rowSize && cardIndex < cards.size(); col++) {
            row.push_back(new CardSlot(cards[cardIndex++], pyramid.size(), col, false));
        }
        pyramid.push_back(row);
    }
    
    totalRows = pyramid.size();
}

std::vector<Card*> CardStructure::getAccessibleCards() {
    std::vector<Card*> accessible;
    
    for (auto& row : pyramid) {
        for (auto* slot : row) {
            if (slot->isAccessible(pyramid)) {
                // 如果卡牌面朝下,翻开它
                if (slot->isFaceDown()) {
                    slot->reveal();
                }
                accessible.push_back(slot->getCard());
            }
        }
    }
    
    return accessible;
}

void CardStructure::removeCard(Card* card) {
    for (auto& row : pyramid) {
        for (auto* slot : row) {
            if (slot->getCard() == card) {
                slot->remove();
                return;
            }
        }
    }
}

bool CardStructure::isEmpty() const {
    for (const auto& row : pyramid) {
        for (const auto* slot : row) {
            if (!slot->isRemoved()) {
                return false;
            }
        }
    }
    return true;
}

std::string CardStructure::getVisualRepresentation() const {
    std::stringstream ss;
    ss << "\n金字塔结构:\n";
    
    for (size_t i = 0; i < pyramid.size(); i++) {
        // 添加缩进使其看起来像金字塔
        for (size_t j = 0; j < (pyramid.size() - i); j++) {
            ss << "  ";
        }
        
        for (const auto* slot : pyramid[i]) {
            if (slot->isRemoved()) {
                ss << "[  ] ";
            } else if (slot->isFaceDown()) {
                ss << "[??] ";
            } else {
                // 显示卡牌名称的前2个字符
                std::string name = slot->getCard()->getName();
                if (name.length() >= 6) {  // 中文字符
                    ss << "[" << name.substr(0, 6) << "] ";
                } else {
                    ss << "[" << name << "] ";
                }
            }
        }
        ss << "\n";
    }
    
    return ss.str();
}
