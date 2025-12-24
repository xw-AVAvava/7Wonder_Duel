#include "../../include/resources/Cost.h"
#include <sstream>

Cost::Cost() : coins(0) {}

Cost::Cost(int coins) : coins(coins) {}

void Cost::addResource(ResourceType type, int quantity) {
    resources[type] += quantity;
}

void Cost::addCoins(int amount) {
    coins += amount;
}

bool Cost::isEmpty() const {
    return resources.empty() && coins == 0;
}

const std::map<ResourceType, int>& Cost::getResources() const {
    return resources;
}

int Cost::getCoins() const {
    return coins;
}

std::string Cost::toString() const {
    if (isEmpty()) {
        return "免费";
    }
    
    std::stringstream ss;
    bool first = true;
    
    for (const auto& pair : resources) {
        if (!first) ss << " + ";
        ss << pair.second << resourceTypeToString(pair.first);
        first = false;
    }
    
    if (coins > 0) {
        if (!first) ss << " + ";
        ss << coins << "金币";
    }
    
    return ss.str();
}
