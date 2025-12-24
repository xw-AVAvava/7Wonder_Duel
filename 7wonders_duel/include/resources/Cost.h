#ifndef COST_H
#define COST_H

#include "../Types.h"
#include <map>

class Cost {
private:
    std::map<ResourceType, int> resources;
    int coins;

public:
    Cost();
    Cost(int coins);
    
    void addResource(ResourceType type, int quantity);
    void addCoins(int amount);
    
    bool isEmpty() const;
    const std::map<ResourceType, int>& getResources() const;
    int getCoins() const;
    
    std::string toString() const;
};

#endif // COST_H
